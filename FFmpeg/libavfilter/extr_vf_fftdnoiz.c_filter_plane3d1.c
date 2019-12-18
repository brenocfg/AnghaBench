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
struct TYPE_5__ {int const sigma; float amount; TYPE_1__* planes; } ;
struct TYPE_4__ {int b; int nox; int noy; int buffer_linesize; float** buffer; } ;
typedef  TYPE_1__ PlaneContext ;
typedef  TYPE_2__ FFTdnoizContext ;

/* Variables and functions */
 size_t CURRENT ; 
 float FFMAX (float const,float) ; 

__attribute__((used)) static void filter_plane3d1(FFTdnoizContext *s, int plane, float *pbuffer)
{
    PlaneContext *p = &s->planes[plane];
    const int block = p->b;
    const int nox = p->nox;
    const int noy = p->noy;
    const int buffer_linesize = p->buffer_linesize / sizeof(float);
    const float sigma = s->sigma * s->sigma * block * block;
    const float limit = 1.f - s->amount;
    float *cbuffer = p->buffer[CURRENT];
    int y, x, i, j;

    for (y = 0; y < noy; y++) {
        for (x = 0; x < nox; x++) {
            float *cbuff = cbuffer + buffer_linesize * y * block + x * block * 2;
            float *pbuff = pbuffer + buffer_linesize * y * block + x * block * 2;

            for (i = 0; i < block; i++) {
                for (j = 0; j < block; j++) {
                    float factor, power, re, im, pre, pim;
                    float sumr, sumi, difr, difi;

                    re = cbuff[j * 2    ];
                    pre = pbuff[j * 2    ];
                    im = cbuff[j * 2 + 1];
                    pim = pbuff[j * 2 + 1];

                    sumr = re + pre;
                    sumi = im + pim;
                    difr = re - pre;
                    difi = im - pim;

                    power = sumr * sumr + sumi * sumi + 1e-15f;
                    factor = FFMAX(limit, (power - sigma) / power);
                    sumr *= factor;
                    sumi *= factor;
                    power = difr * difr + difi * difi + 1e-15f;
                    factor = FFMAX(limit, (power - sigma) / power);
                    difr *= factor;
                    difi *= factor;

                    cbuff[j * 2    ] = (sumr + difr) * 0.5f;
                    cbuff[j * 2 + 1] = (sumi + difi) * 0.5f;
                }

                cbuff += buffer_linesize;
                pbuff += buffer_linesize;
            }
        }
    }
}