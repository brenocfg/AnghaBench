#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_5__ {int height; int width; TYPE_1__* bands; } ;
struct TYPE_4__ {int pitch; short* buf; } ;
typedef  TYPE_2__ IVIPlaneDesc ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (int) ; 

void ff_ivi_recompose_haar(const IVIPlaneDesc *plane, uint8_t *dst,
                           const ptrdiff_t dst_pitch)
{
    int             x, y, indx, b0, b1, b2, b3, p0, p1, p2, p3;
    const short     *b0_ptr, *b1_ptr, *b2_ptr, *b3_ptr;
    ptrdiff_t       pitch;

    /* all bands should have the same pitch */
    pitch = plane->bands[0].pitch;

    /* get pointers to the wavelet bands */
    b0_ptr = plane->bands[0].buf;
    b1_ptr = plane->bands[1].buf;
    b2_ptr = plane->bands[2].buf;
    b3_ptr = plane->bands[3].buf;

    for (y = 0; y < plane->height; y += 2) {
        for (x = 0, indx = 0; x < plane->width; x += 2, indx++) {
            /* load coefficients */
            b0 = b0_ptr[indx]; //should be: b0 = (num_bands > 0) ? b0_ptr[indx] : 0;
            b1 = b1_ptr[indx]; //should be: b1 = (num_bands > 1) ? b1_ptr[indx] : 0;
            b2 = b2_ptr[indx]; //should be: b2 = (num_bands > 2) ? b2_ptr[indx] : 0;
            b3 = b3_ptr[indx]; //should be: b3 = (num_bands > 3) ? b3_ptr[indx] : 0;

            /* haar wavelet recomposition */
            p0 = (b0 + b1 + b2 + b3 + 2) >> 2;
            p1 = (b0 + b1 - b2 - b3 + 2) >> 2;
            p2 = (b0 - b1 + b2 - b3 + 2) >> 2;
            p3 = (b0 - b1 - b2 + b3 + 2) >> 2;

            /* bias, convert and output four pixels */
            dst[x]                 = av_clip_uint8(p0 + 128);
            dst[x + 1]             = av_clip_uint8(p1 + 128);
            dst[dst_pitch + x]     = av_clip_uint8(p2 + 128);
            dst[dst_pitch + x + 1] = av_clip_uint8(p3 + 128);
        }// for x

        dst += dst_pitch << 1;

        b0_ptr += pitch;
        b1_ptr += pitch;
        b2_ptr += pitch;
        b3_ptr += pitch;
    }// for y
}