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
typedef  size_t ptrdiff_t ;
typedef  int int32_t ;
struct TYPE_5__ {int height; int width; TYPE_1__* bands; } ;
struct TYPE_4__ {size_t pitch; short* buf; } ;
typedef  TYPE_2__ IVIPlaneDesc ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (int) ; 

void ff_ivi_recompose53(const IVIPlaneDesc *plane, uint8_t *dst,
                        const ptrdiff_t dst_pitch)
{
    int             x, y, indx;
    int32_t         p0, p1, p2, p3, tmp0, tmp1, tmp2;
    int32_t         b0_1, b0_2, b1_1, b1_2, b1_3, b2_1, b2_2, b2_3, b2_4, b2_5, b2_6;
    int32_t         b3_1, b3_2, b3_3, b3_4, b3_5, b3_6, b3_7, b3_8, b3_9;
    ptrdiff_t       pitch, back_pitch;
    const short     *b0_ptr, *b1_ptr, *b2_ptr, *b3_ptr;
    const int       num_bands = 4;

    /* all bands should have the same pitch */
    pitch = plane->bands[0].pitch;

    /* pixels at the position "y-1" will be set to pixels at the "y" for the 1st iteration */
    back_pitch = 0;

    /* get pointers to the wavelet bands */
    b0_ptr = plane->bands[0].buf;
    b1_ptr = plane->bands[1].buf;
    b2_ptr = plane->bands[2].buf;
    b3_ptr = plane->bands[3].buf;

    for (y = 0; y < plane->height; y += 2) {

        if (y+2 >= plane->height)
            pitch= 0;
        /* load storage variables with values */
        if (num_bands > 0) {
            b0_1 = b0_ptr[0];
            b0_2 = b0_ptr[pitch];
        }

        if (num_bands > 1) {
            b1_1 = b1_ptr[back_pitch];
            b1_2 = b1_ptr[0];
            b1_3 = b1_1 - b1_2*6 + b1_ptr[pitch];
        }

        if (num_bands > 2) {
            b2_2 = b2_ptr[0];     // b2[x,  y  ]
            b2_3 = b2_2;          // b2[x+1,y  ] = b2[x,y]
            b2_5 = b2_ptr[pitch]; // b2[x  ,y+1]
            b2_6 = b2_5;          // b2[x+1,y+1] = b2[x,y+1]
        }

        if (num_bands > 3) {
            b3_2 = b3_ptr[back_pitch]; // b3[x  ,y-1]
            b3_3 = b3_2;               // b3[x+1,y-1] = b3[x  ,y-1]
            b3_5 = b3_ptr[0];          // b3[x  ,y  ]
            b3_6 = b3_5;               // b3[x+1,y  ] = b3[x  ,y  ]
            b3_8 = b3_2 - b3_5*6 + b3_ptr[pitch];
            b3_9 = b3_8;
        }

        for (x = 0, indx = 0; x < plane->width; x+=2, indx++) {
            if (x+2 >= plane->width) {
                b0_ptr --;
                b1_ptr --;
                b2_ptr --;
                b3_ptr --;
            }

            /* some values calculated in the previous iterations can */
            /* be reused in the next ones, so do appropriate copying */
            b2_1 = b2_2; // b2[x-1,y  ] = b2[x,  y  ]
            b2_2 = b2_3; // b2[x  ,y  ] = b2[x+1,y  ]
            b2_4 = b2_5; // b2[x-1,y+1] = b2[x  ,y+1]
            b2_5 = b2_6; // b2[x  ,y+1] = b2[x+1,y+1]
            b3_1 = b3_2; // b3[x-1,y-1] = b3[x  ,y-1]
            b3_2 = b3_3; // b3[x  ,y-1] = b3[x+1,y-1]
            b3_4 = b3_5; // b3[x-1,y  ] = b3[x  ,y  ]
            b3_5 = b3_6; // b3[x  ,y  ] = b3[x+1,y  ]
            b3_7 = b3_8; // vert_HPF(x-1)
            b3_8 = b3_9; // vert_HPF(x  )

            p0 = p1 = p2 = p3 = 0;

            /* process the LL-band by applying LPF both vertically and horizontally */
            if (num_bands > 0) {
                tmp0 = b0_1;
                tmp2 = b0_2;
                b0_1 = b0_ptr[indx+1];
                b0_2 = b0_ptr[pitch+indx+1];
                tmp1 = tmp0 + b0_1;

                p0 =  tmp0 * 16;
                p1 =  tmp1 * 8;
                p2 = (tmp0 + tmp2) * 8;
                p3 = (tmp1 + tmp2 + b0_2) * 4;
            }

            /* process the HL-band by applying HPF vertically and LPF horizontally */
            if (num_bands > 1) {
                tmp0 = b1_2;
                tmp1 = b1_1;
                b1_2 = b1_ptr[indx+1];
                b1_1 = b1_ptr[back_pitch+indx+1];

                tmp2 = tmp1 - tmp0*6 + b1_3;
                b1_3 = b1_1 - b1_2*6 + b1_ptr[pitch+indx+1];

                p0 += (tmp0 + tmp1) * 8;
                p1 += (tmp0 + tmp1 + b1_1 + b1_2) * 4;
                p2 +=  tmp2 * 4;
                p3 += (tmp2 + b1_3) * 2;
            }

            /* process the LH-band by applying LPF vertically and HPF horizontally */
            if (num_bands > 2) {
                b2_3 = b2_ptr[indx+1];
                b2_6 = b2_ptr[pitch+indx+1];

                tmp0 = b2_1 + b2_2;
                tmp1 = b2_1 - b2_2*6 + b2_3;

                p0 += tmp0 * 8;
                p1 += tmp1 * 4;
                p2 += (tmp0 + b2_4 + b2_5) * 4;
                p3 += (tmp1 + b2_4 - b2_5*6 + b2_6) * 2;
            }

            /* process the HH-band by applying HPF both vertically and horizontally */
            if (num_bands > 3) {
                b3_6 = b3_ptr[indx+1];            // b3[x+1,y  ]
                b3_3 = b3_ptr[back_pitch+indx+1]; // b3[x+1,y-1]

                tmp0 = b3_1 + b3_4;
                tmp1 = b3_2 + b3_5;
                tmp2 = b3_3 + b3_6;

                b3_9 = b3_3 - b3_6*6 + b3_ptr[pitch+indx+1];

                p0 += (tmp0 + tmp1) * 4;
                p1 += (tmp0 - tmp1*6 + tmp2) * 2;
                p2 += (b3_7 + b3_8) * 2;
                p3 +=  b3_7 - b3_8*6 + b3_9;
            }

            /* output four pixels */
            dst[x]             = av_clip_uint8((p0 >> 6) + 128);
            dst[x+1]           = av_clip_uint8((p1 >> 6) + 128);
            dst[dst_pitch+x]   = av_clip_uint8((p2 >> 6) + 128);
            dst[dst_pitch+x+1] = av_clip_uint8((p3 >> 6) + 128);
        }// for x

        dst += dst_pitch << 1;

        back_pitch = -pitch;

        b0_ptr += pitch + 1;
        b1_ptr += pitch + 1;
        b2_ptr += pitch + 1;
        b3_ptr += pitch + 1;
    }
}