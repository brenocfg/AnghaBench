#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int naxis; int* naxisn; int bitpix; int data_min; int bzero; int bscale; int data_max; scalar_t__ rgb; int /*<<< orphan*/  data_max_found; int /*<<< orphan*/  data_min_found; scalar_t__ blank_found; } ;
typedef  TYPE_1__ FITSHeader ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  STATE_BITPIX ; 
 int abs (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_fits_header_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int avpriv_fits_header_parse_line (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ***) ; 
 int fill_data_min_max (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int fits_read_header(AVCodecContext *avctx, const uint8_t **ptr, FITSHeader *header,
                            const uint8_t *end, AVDictionary **metadata)
{
    const uint8_t *ptr8 = *ptr;
    int lines_read, bytes_left, i, ret;
    size_t size;

    lines_read = 1; // to account for first header line, SIMPLE or XTENSION which is not included in packet...
    avpriv_fits_header_init(header, STATE_BITPIX);
    do {
        if (end - ptr8 < 80)
            return AVERROR_INVALIDDATA;
        ret = avpriv_fits_header_parse_line(avctx, header, ptr8, &metadata);
        ptr8 += 80;
        lines_read++;
    } while (!ret);
    if (ret < 0)
        return ret;

    bytes_left = (((lines_read + 35) / 36) * 36 - lines_read) * 80;
    if (end - ptr8 < bytes_left)
        return AVERROR_INVALIDDATA;
    ptr8 += bytes_left;

    if (header->rgb && (header->naxis != 3 || (header->naxisn[2] != 3 && header->naxisn[2] != 4))) {
        av_log(avctx, AV_LOG_ERROR, "File contains RGB image but NAXIS = %d and NAXIS3 = %d\n", header->naxis, header->naxisn[2]);
        return AVERROR_INVALIDDATA;
    }

    if (!header->rgb && header->naxis != 2) {
        av_log(avctx, AV_LOG_ERROR, "unsupported number of dimensions, NAXIS = %d\n", header->naxis);
        return AVERROR_INVALIDDATA;
    }

    if (header->blank_found && (header->bitpix == -32 || header->bitpix == -64)) {
        av_log(avctx, AV_LOG_WARNING, "BLANK keyword found but BITPIX = %d\n. Ignoring BLANK", header->bitpix);
        header->blank_found = 0;
    }

    size = abs(header->bitpix) >> 3;
    for (i = 0; i < header->naxis; i++) {
        if (size == 0 || header->naxisn[i] > SIZE_MAX / size) {
            av_log(avctx, AV_LOG_ERROR, "unsupported size of FITS image");
            return AVERROR_INVALIDDATA;
        }
        size *= header->naxisn[i];
    }

    if (end - ptr8 < size)
        return AVERROR_INVALIDDATA;
    *ptr = ptr8;

    if (!header->rgb && (!header->data_min_found || !header->data_max_found)) {
        ret = fill_data_min_max(ptr8, header, end);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "invalid BITPIX, %d\n", header->bitpix);
            return ret;
        }
    } else {
        /*
         * instead of applying bscale and bzero to every element,
         * we can do inverse transformation on data_min and data_max
         */
        header->data_min = (header->data_min - header->bzero) / header->bscale;
        header->data_max = (header->data_max - header->bzero) / header->bscale;
    }
    if (!header->rgb && header->data_min >= header->data_max) {
        if (header->data_min > header->data_max) {
            av_log(avctx, AV_LOG_ERROR, "data min/max (%g %g) is invalid\n", header->data_min, header->data_max);
            return AVERROR_INVALIDDATA;
        }
        av_log(avctx, AV_LOG_WARNING, "data min/max indicates a blank image\n");
        header->data_max ++;
    }

    return 0;
}