#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int block_size; int* planewidth; int pgroup_size; int group_size; float sigma; int /*<<< orphan*/  (* get_block_row ) (int /*<<< orphan*/  const*,int,int const,int const,int const,float*) ;TYPE_2__* slices; } ;
struct TYPE_6__ {int nb_match_blocks; float* buffer; float* bufferh; float* bufferv; float* bufferz; float* rbuffer; float* rbufferh; float* rbufferv; float* rbufferz; float* num; float* den; int /*<<< orphan*/  dcti; int /*<<< orphan*/  gdcti; int /*<<< orphan*/  gdctf; int /*<<< orphan*/  dctf; TYPE_1__* match_blocks; } ;
struct TYPE_5__ {int y; int x; } ;
typedef  TYPE_2__ SliceContext ;
typedef  TYPE_3__ BM3DContext ;

/* Variables and functions */
 float FFMAX (float,float) ; 
 int /*<<< orphan*/  av_dct_calc (int /*<<< orphan*/ ,float*) ; 
 scalar_t__ isnan (float) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int,int const,int const,int const,float*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,int,int const,int const,int const,float*) ; 

__attribute__((used)) static void final_block_filtering(BM3DContext *s, const uint8_t *src, int src_linesize,
                                  const uint8_t *ref, int ref_linesize,
                                  int y, int x, int plane, int jobnr)
{
    SliceContext *sc = &s->slices[jobnr];
    const int buffer_linesize = s->block_size * s->block_size;
    const int nb_match_blocks = sc->nb_match_blocks;
    const int block_size = s->block_size;
    const int width = s->planewidth[plane];
    const int pgroup_size = s->pgroup_size;
    const int group_size = s->group_size;
    const float sigma_sqr = s->sigma * s->sigma;
    float *buffer = sc->buffer;
    float *bufferh = sc->bufferh;
    float *bufferv = sc->bufferv;
    float *bufferz = sc->bufferz;
    float *rbuffer = sc->rbuffer;
    float *rbufferh = sc->rbufferh;
    float *rbufferv = sc->rbufferv;
    float *rbufferz = sc->rbufferz;
    float den_weight, num_weight;
    float l2_wiener = 0;
    int i, j, k;

    for (k = 0; k < nb_match_blocks; k++) {
        const int y = sc->match_blocks[k].y;
        const int x = sc->match_blocks[k].x;

        for (i = 0; i < block_size; i++) {
            s->get_block_row(src, src_linesize, y + i, x, block_size, bufferh + block_size * i);
            s->get_block_row(ref, ref_linesize, y + i, x, block_size, rbufferh + block_size * i);
            av_dct_calc(sc->dctf, bufferh + block_size * i);
            av_dct_calc(sc->dctf, rbufferh + block_size * i);
        }

        for (i = 0; i < block_size; i++) {
            for (j = 0; j < block_size; j++) {
                bufferv[i * block_size + j] = bufferh[j * block_size + i];
                rbufferv[i * block_size + j] = rbufferh[j * block_size + i];
            }
            av_dct_calc(sc->dctf, bufferv + i * block_size);
            av_dct_calc(sc->dctf, rbufferv + i * block_size);
        }

        for (i = 0; i < block_size; i++) {
            memcpy(buffer + k * buffer_linesize + i * block_size,
                   bufferv + i * block_size, block_size * 4);
            memcpy(rbuffer + k * buffer_linesize + i * block_size,
                   rbufferv + i * block_size, block_size * 4);
        }
    }

    for (i = 0; i < block_size; i++) {
        for (j = 0; j < block_size; j++) {
            for (k = 0; k < nb_match_blocks; k++) {
                bufferz[k] = buffer[buffer_linesize * k + i * block_size + j];
                rbufferz[k] = rbuffer[buffer_linesize * k + i * block_size + j];
            }
            if (group_size > 1) {
                av_dct_calc(sc->gdctf, bufferz);
                av_dct_calc(sc->gdctf, rbufferz);
            }
            bufferz += pgroup_size;
            rbufferz += pgroup_size;
        }
    }

    bufferz = sc->bufferz;
    rbufferz = sc->rbufferz;

    for (i = 0; i < block_size; i++) {
        for (j = 0; j < block_size; j++) {
            for (k = 0; k < nb_match_blocks; k++) {
                const float ref_sqr = rbufferz[k] * rbufferz[k];
                float wiener_coef = ref_sqr / (ref_sqr + sigma_sqr);

                if (isnan(wiener_coef))
                   wiener_coef = 1;
                bufferz[k] *= wiener_coef;
                l2_wiener += wiener_coef * wiener_coef;
            }
            bufferz += pgroup_size;
            rbufferz += pgroup_size;
        }
    }

    bufferz = sc->bufferz;
    buffer = sc->buffer;
    for (i = 0; i < block_size; i++) {
        for (j = 0; j < block_size; j++) {
            if (group_size > 1)
                av_dct_calc(sc->gdcti, bufferz);
            for (k = 0; k < nb_match_blocks; k++) {
                buffer[buffer_linesize * k + i * block_size + j] = bufferz[k];
            }
            bufferz += pgroup_size;
        }
    }

    l2_wiener = FFMAX(l2_wiener, 1e-15f);
    den_weight = 1.f / l2_wiener;
    num_weight = den_weight;

    for (k = 0; k < nb_match_blocks; k++) {
        float *num = sc->num + y * width + x;
        float *den = sc->den + y * width + x;

        for (i = 0; i < block_size; i++) {
            memcpy(bufferv + i * block_size,
                   buffer + k * buffer_linesize + i * block_size,
                   block_size * 4);
        }

        for (i = 0; i < block_size; i++) {
            av_dct_calc(sc->dcti, bufferv + block_size * i);
            for (j = 0; j < block_size; j++) {
                bufferh[j * block_size + i] = bufferv[i * block_size + j];
            }
        }

        for (i = 0; i < block_size; i++) {
            av_dct_calc(sc->dcti, bufferh + block_size * i);
            for (j = 0; j < block_size; j++) {
                num[j] += bufferh[i * block_size + j] * num_weight;
                den[j] += den_weight;
            }
            num += width;
            den += width;
        }
    }
}