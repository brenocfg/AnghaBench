#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_BGR4_BYTE 132 
#define  AV_PIX_FMT_BGR8 131 
#define  AV_PIX_FMT_GRAY8 130 
#define  AV_PIX_FMT_RGB4_BYTE 129 
#define  AV_PIX_FMT_RGB8 128 
 int /*<<< orphan*/  EINVAL ; 

int avpriv_set_systematic_pal2(uint32_t pal[256], enum AVPixelFormat pix_fmt)
{
    int i;

    for (i = 0; i < 256; i++) {
        int r, g, b;

        switch (pix_fmt) {
        case AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            break;
        case AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            break;
        case AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            break;
        case AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            break;
        case AV_PIX_FMT_GRAY8:
            r = b = g = i;
            break;
        default:
            return AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    return 0;
}