#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int extradata_size; int format; int bits_per_coded_sample; int width; int codec_tag; int height; scalar_t__ extradata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int AV_PIX_FMT_MONOBLACK ; 
 int AV_PIX_FMT_MONOWHITE ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char*,int) ; 

void ff_put_bmp_header(AVIOContext *pb, AVCodecParameters *par,
                       int for_asf, int ignore_extradata)
{
    int keep_height = par->extradata_size >= 9 &&
                      !memcmp(par->extradata + par->extradata_size - 9, "BottomUp", 9);
    int extradata_size = par->extradata_size - 9*keep_height;
    enum AVPixelFormat pix_fmt = par->format;
    int pal_avi;

    if (pix_fmt == AV_PIX_FMT_NONE && par->bits_per_coded_sample == 1)
        pix_fmt = AV_PIX_FMT_MONOWHITE;
    pal_avi = !for_asf &&
              (pix_fmt == AV_PIX_FMT_PAL8 ||
               pix_fmt == AV_PIX_FMT_MONOWHITE ||
               pix_fmt == AV_PIX_FMT_MONOBLACK);

    /* Size (not including the size of the color table or color masks) */
    avio_wl32(pb, 40 + (ignore_extradata || pal_avi ? 0 : extradata_size));
    avio_wl32(pb, par->width);
    //We always store RGB TopDown
    avio_wl32(pb, par->codec_tag || keep_height ? par->height : -par->height);
    /* planes */
    avio_wl16(pb, 1);
    /* depth */
    avio_wl16(pb, par->bits_per_coded_sample ? par->bits_per_coded_sample : 24);
    /* compression type */
    avio_wl32(pb, par->codec_tag);
    avio_wl32(pb, (par->width * par->height * (par->bits_per_coded_sample ? par->bits_per_coded_sample : 24)+7) / 8);
    avio_wl32(pb, 0);
    avio_wl32(pb, 0);
    /* Number of color indices in the color table that are used.
     * A value of 0 means 2^biBitCount indices, but this doesn't work
     * with Windows Media Player and files containing xxpc chunks. */
    avio_wl32(pb, pal_avi ? 1 << par->bits_per_coded_sample : 0);
    avio_wl32(pb, 0);

    if (!ignore_extradata) {
        if (par->extradata_size) {
            avio_write(pb, par->extradata, extradata_size);
            if (!for_asf && extradata_size & 1)
                avio_w8(pb, 0);
        } else if (pal_avi) {
            int i;
            for (i = 0; i < 1 << par->bits_per_coded_sample; i++) {
                /* Initialize 1 bpp palette to black & white */
                if (i == 0 && pix_fmt == AV_PIX_FMT_MONOWHITE)
                    avio_wl32(pb, 0xffffff);
                else if (i == 1 && pix_fmt == AV_PIX_FMT_MONOBLACK)
                    avio_wl32(pb, 0xffffff);
                else
                    avio_wl32(pb, 0);
            }
        }
    }
}