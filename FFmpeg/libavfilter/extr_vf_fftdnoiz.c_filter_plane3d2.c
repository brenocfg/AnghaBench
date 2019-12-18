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
 float FFMAX (float,float const) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void filter_plane3d2(FFTdnoizContext *s, int plane, float *pbuffer, float *nbuffer)
{
    PlaneContext *p = &s->planes[plane];
    const int block = p->b;
    const int nox = p->nox;
    const int noy = p->noy;
    const int buffer_linesize = p->buffer_linesize / sizeof(float);
    const float sigma = s->sigma * s->sigma * block * block;
    const float limit = 1.f - s->amount;
    float *cbuffer = p->buffer[CURRENT];
    const float cfactor = sqrtf(3.f) * 0.5f;
    const float scale = 1.f / 3.f;
    int y, x, i, j;

    for (y = 0; y < noy; y++) {
        for (x = 0; x < nox; x++) {
            float *cbuff = cbuffer + buffer_linesize * y * block + x * block * 2;
            float *pbuff = pbuffer + buffer_linesize * y * block + x * block * 2;
            float *nbuff = nbuffer + buffer_linesize * y * block + x * block * 2;

            for (i = 0; i < block; i++) {
                for (j = 0; j < block; j++) {
                    float sumr, sumi, difr, difi, mpr, mpi, mnr, mni;
                    float factor, power, sumpnr, sumpni;

                    sumpnr = pbuff[2 * j    ] + nbuff[2 * j    ];
                    sumpni = pbuff[2 * j + 1] + nbuff[2 * j + 1];
                    sumr = cbuff[2 * j    ] + sumpnr;
                    sumi = cbuff[2 * j + 1] + sumpni;
                    difr = cfactor * (nbuff[2 * j    ] - pbuff[2 * j    ]);
                    difi = cfactor * (pbuff[2 * j + 1] - nbuff[2 * j + 1]);
                    mpr = cbuff[2 * j    ] - 0.5f * sumpnr + difi;
                    mnr = mpr - difi - difi;
                    mpi = cbuff[2 * j + 1] - 0.5f * sumpni + difr;
                    mni = mpi - difr - difr;
                    power = sumr * sumr + sumi * sumi + 1e-15f;
                    factor = FFMAX((power - sigma) / power, limit);
                    sumr *= factor;
                    sumi *= factor;
                    power = mpr * mpr + mpi * mpi + 1e-15f;
                    factor = FFMAX((power - sigma) / power, limit);
                    mpr *= factor;
                    mpi *= factor;
                    power = mnr * mnr + mni * mni + 1e-15f;
                    factor = FFMAX((power - sigma) / power, limit);
                    mnr *= factor;
                    mni *= factor;
                    cbuff[2 * j    ] = (sumr + mpr + mnr) * scale;
                    cbuff[2 * j + 1] = (sumi + mpi + mni) * scale;

                }

                cbuff += buffer_linesize;
                pbuff += buffer_linesize;
                nbuff += buffer_linesize;
            }
        }
    }
}