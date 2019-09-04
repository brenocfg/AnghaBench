#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_4__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  lzws; scalar_t__ buf_start; scalar_t__* buf; scalar_t__ buf_size; } ;
typedef  TYPE_1__ TiffEncoderContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
#define  TIFF_LZW 130 
#define  TIFF_PACKBITS 129 
#define  TIFF_RAW 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  check_size (TYPE_1__*,int) ; 
 int ff_lzw_encode (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int ff_rle_encode (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/  const*,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int encode_strip(TiffEncoderContext *s, const int8_t *src,
                        uint8_t *dst, int n, int compr)
{
    switch (compr) {
#if CONFIG_ZLIB
    case TIFF_DEFLATE:
    case TIFF_ADOBE_DEFLATE:
    {
        unsigned long zlen = s->buf_size - (*s->buf - s->buf_start);
        if (compress(dst, &zlen, src, n) != Z_OK) {
            av_log(s->avctx, AV_LOG_ERROR, "Compressing failed\n");
            return AVERROR_EXTERNAL;
        }
        return zlen;
    }
#endif
    case TIFF_RAW:
        if (check_size(s, n))
            return AVERROR(EINVAL);
        memcpy(dst, src, n);
        return n;
    case TIFF_PACKBITS:
        return ff_rle_encode(dst, s->buf_size - (*s->buf - s->buf_start),
                             src, 1, n, 2, 0xff, -1, 0);
    case TIFF_LZW:
        return ff_lzw_encode(s->lzws, src, n);
    default:
        av_log(s->avctx, AV_LOG_ERROR, "Unsupported compression method: %d\n",
               compr);
        return AVERROR(EINVAL);
    }
}