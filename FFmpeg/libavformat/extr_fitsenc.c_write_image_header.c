#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_10__ {int format; int width; int height; } ;
struct TYPE_9__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; TYPE_2__** streams; } ;
struct TYPE_8__ {TYPE_4__* codecpar; } ;
struct TYPE_7__ {scalar_t__ first_image; } ;
typedef  TYPE_1__ FITSContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_GBRAP 133 
#define  AV_PIX_FMT_GBRAP16BE 132 
#define  AV_PIX_FMT_GBRP 131 
#define  AV_PIX_FMT_GBRP16BE 130 
#define  AV_PIX_FMT_GRAY16BE 129 
#define  AV_PIX_FMT_GRAY8 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  write_keyword_value (TYPE_3__*,char*,int,int*) ; 

__attribute__((used)) static int write_image_header(AVFormatContext *s)
{
    AVStream *st = s->streams[0];
    AVCodecParameters *encctx = st->codecpar;
    FITSContext *fitsctx = s->priv_data;
    uint8_t buffer[80];
    int bitpix, naxis, naxis3 = 1, bzero = 0, rgb = 0, lines_written = 0, lines_left;

    switch (encctx->format) {
        case AV_PIX_FMT_GRAY8:
            bitpix = 8;
            naxis = 2;
            break;
        case AV_PIX_FMT_GRAY16BE:
            bitpix = 16;
            naxis = 2;
            bzero = 32768;
            break;
        case AV_PIX_FMT_GBRP:
        case AV_PIX_FMT_GBRAP:
            bitpix = 8;
            naxis = 3;
            rgb = 1;
            if (encctx->format == AV_PIX_FMT_GBRP) {
                naxis3 = 3;
            } else {
                naxis3 = 4;
            }
            break;
        case AV_PIX_FMT_GBRP16BE:
        case AV_PIX_FMT_GBRAP16BE:
            bitpix = 16;
            naxis = 3;
            rgb = 1;
            if (encctx->format == AV_PIX_FMT_GBRP16BE) {
                naxis3 = 3;
            } else {
                naxis3 = 4;
            }
            bzero = 32768;
            break;
        default:
            return AVERROR(EINVAL);
    }

    if (fitsctx->first_image) {
        memcpy(buffer, "SIMPLE  = ", 10);
        memset(buffer + 10, ' ', 70);
        buffer[29] = 'T';
        avio_write(s->pb, buffer, sizeof(buffer));
    } else {
        memcpy(buffer, "XTENSION= 'IMAGE   '", 20);
        memset(buffer + 20, ' ', 60);
        avio_write(s->pb, buffer, sizeof(buffer));
    }
    lines_written++;

    write_keyword_value(s, "BITPIX", bitpix, &lines_written);         // no of bits per pixel
    write_keyword_value(s, "NAXIS", naxis, &lines_written);           // no of dimensions of image
    write_keyword_value(s, "NAXIS1", encctx->width, &lines_written);   // first dimension i.e. width
    write_keyword_value(s, "NAXIS2", encctx->height, &lines_written);  // second dimension i.e. height

    if (rgb)
        write_keyword_value(s, "NAXIS3", naxis3, &lines_written);     // third dimension to store RGBA planes

    if (!fitsctx->first_image) {
        write_keyword_value(s, "PCOUNT", 0, &lines_written);
        write_keyword_value(s, "GCOUNT", 1, &lines_written);
    } else {
        fitsctx->first_image = 0;
    }

    /*
     * Since FITS does not support unsigned 16 bit integers,
     * BZERO = 32768 is used to store unsigned 16 bit integers as
     * signed integers so that it can be read properly.
     */
    if (bitpix == 16)
        write_keyword_value(s, "BZERO", bzero, &lines_written);

    if (rgb) {
        memcpy(buffer, "CTYPE3  = 'RGB     '", 20);
        memset(buffer + 20, ' ', 60);
        avio_write(s->pb, buffer, sizeof(buffer));
        lines_written++;
    }

    memcpy(buffer, "END", 3);
    memset(buffer + 3, ' ', 77);
    avio_write(s->pb, buffer, sizeof(buffer));
    lines_written++;

    lines_left = ((lines_written + 35) / 36) * 36 - lines_written;
    memset(buffer, ' ', 80);
    while (lines_left > 0) {
        avio_write(s->pb, buffer, sizeof(buffer));
        lines_left--;
    }
    return 0;
}