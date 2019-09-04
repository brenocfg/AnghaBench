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
struct TYPE_4__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_1__*,float*,float const*) ;} ;
typedef  TYPE_1__ FFTContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,float*,float const*) ; 

__attribute__((used)) static void synth_filter_float_64(FFTContext *imdct,
                                  float *synth_buf_ptr, int *synth_buf_offset,
                                  float synth_buf2[64], const float window[1024],
                                  float out[64], const float in[64], float scale)
{
    float *synth_buf = synth_buf_ptr + *synth_buf_offset;
    int i, j;

    imdct->imdct_half(imdct, synth_buf, in);

    for (i = 0; i < 32; i++) {
        float a = synth_buf2[i     ];
        float b = synth_buf2[i + 32];
        float c = 0;
        float d = 0;
        for (j = 0; j < 1024 - *synth_buf_offset; j += 128) {
            a += window[i + j     ] * (-synth_buf[31 - i + j       ]);
            b += window[i + j + 32] * ( synth_buf[     i + j       ]);
            c += window[i + j + 64] * ( synth_buf[32 + i + j       ]);
            d += window[i + j + 96] * ( synth_buf[63 - i + j       ]);
        }
        for (     ; j < 1024; j += 128) {
            a += window[i + j     ] * (-synth_buf[31 - i + j - 1024]);
            b += window[i + j + 32] * ( synth_buf[     i + j - 1024]);
            c += window[i + j + 64] * ( synth_buf[32 + i + j - 1024]);
            d += window[i + j + 96] * ( synth_buf[63 - i + j - 1024]);
        }
        out[i     ] = a * scale;
        out[i + 32] = b * scale;
        synth_buf2[i     ] = c;
        synth_buf2[i + 32] = d;
    }

    *synth_buf_offset = (*synth_buf_offset - 64) & 1023;
}