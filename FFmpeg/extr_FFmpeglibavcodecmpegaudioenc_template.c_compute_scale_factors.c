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
struct TYPE_3__ {int* scale_factor_table; int* scale_diff_table; } ;
typedef  TYPE_1__ MpegAudioContext ;

/* Variables and functions */
 int /*<<< orphan*/  SBLIMIT ; 
 int abs (int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,int,unsigned char,unsigned char,unsigned char,int,...) ; 

__attribute__((used)) static void compute_scale_factors(MpegAudioContext *s,
                                  unsigned char scale_code[SBLIMIT],
                                  unsigned char scale_factors[SBLIMIT][3],
                                  int sb_samples[3][12][SBLIMIT],
                                  int sblimit)
{
    int *p, vmax, v, n, i, j, k, code;
    int index, d1, d2;
    unsigned char *sf = &scale_factors[0][0];

    for(j=0;j<sblimit;j++) {
        for(i=0;i<3;i++) {
            /* find the max absolute value */
            p = &sb_samples[i][0][j];
            vmax = abs(*p);
            for(k=1;k<12;k++) {
                p += SBLIMIT;
                v = abs(*p);
                if (v > vmax)
                    vmax = v;
            }
            /* compute the scale factor index using log 2 computations */
            if (vmax > 1) {
                n = av_log2(vmax);
                /* n is the position of the MSB of vmax. now
                   use at most 2 compares to find the index */
                index = (21 - n) * 3 - 3;
                if (index >= 0) {
                    while (vmax <= s->scale_factor_table[index+1])
                        index++;
                } else {
                    index = 0; /* very unlikely case of overflow */
                }
            } else {
                index = 62; /* value 63 is not allowed */
            }

            ff_dlog(NULL, "%2d:%d in=%x %x %d\n",
                    j, i, vmax, s->scale_factor_table[index], index);
            /* store the scale factor */
            av_assert2(index >=0 && index <= 63);
            sf[i] = index;
        }

        /* compute the transmission factor : look if the scale factors
           are close enough to each other */
        d1 = s->scale_diff_table[sf[0] - sf[1] + 64];
        d2 = s->scale_diff_table[sf[1] - sf[2] + 64];

        /* handle the 25 cases */
        switch(d1 * 5 + d2) {
        case 0*5+0:
        case 0*5+4:
        case 3*5+4:
        case 4*5+0:
        case 4*5+4:
            code = 0;
            break;
        case 0*5+1:
        case 0*5+2:
        case 4*5+1:
        case 4*5+2:
            code = 3;
            sf[2] = sf[1];
            break;
        case 0*5+3:
        case 4*5+3:
            code = 3;
            sf[1] = sf[2];
            break;
        case 1*5+0:
        case 1*5+4:
        case 2*5+4:
            code = 1;
            sf[1] = sf[0];
            break;
        case 1*5+1:
        case 1*5+2:
        case 2*5+0:
        case 2*5+1:
        case 2*5+2:
            code = 2;
            sf[1] = sf[2] = sf[0];
            break;
        case 2*5+3:
        case 3*5+3:
            code = 2;
            sf[0] = sf[1] = sf[2];
            break;
        case 3*5+0:
        case 3*5+1:
        case 3*5+2:
            code = 2;
            sf[0] = sf[2] = sf[1];
            break;
        case 1*5+3:
            code = 2;
            if (sf[0] > sf[2])
              sf[0] = sf[2];
            sf[1] = sf[2] = sf[0];
            break;
        default:
            av_assert2(0); //cannot happen
            code = 0;           /* kill warning */
        }

        ff_dlog(NULL, "%d: %2d %2d %2d %d %d -> %d\n", j,
                sf[0], sf[1], sf[2], d1, d2, code);
        scale_code[j] = code;
        sf += 3;
    }
}