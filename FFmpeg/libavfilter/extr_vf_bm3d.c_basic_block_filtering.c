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
struct TYPE_7__ {int block_size; int* planewidth; int pgroup_size; int group_size; float hard_threshold; float sigma; int /*<<< orphan*/  (* get_block_row ) (int /*<<< orphan*/  const*,int,int const,int const,int const,float*) ;TYPE_2__* slices; } ;
struct TYPE_6__ {int nb_match_blocks; float* buffer; float* bufferh; float* bufferv; float* bufferz; float* num; float* den; int /*<<< orphan*/  dcti; int /*<<< orphan*/  gdcti; int /*<<< orphan*/  gdctf; int /*<<< orphan*/  dctf; TYPE_1__* match_blocks; } ;
struct TYPE_5__ {int y; int x; } ;
typedef  TYPE_2__ SliceContext ;
typedef  TYPE_3__ BM3DContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dct_calc (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int const) ; 
 float sqrtf (float) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int,int const,int const,int const,float*) ; 

__attribute__((used)) static void basic_block_filtering(BM3DContext *s, const uint8_t *src, int src_linesize,
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
    float *buffer = sc->buffer;
    float *bufferh = sc->bufferh;
    float *bufferv = sc->bufferv;
    float *bufferz = sc->bufferz;
    float threshold[4];
    float den_weight, num_weight;
    int retained = 0;
    int i, j, k;

    for (k = 0; k < nb_match_blocks; k++) {
        const int y = sc->match_blocks[k].y;
        const int x = sc->match_blocks[k].x;

        for (i = 0; i < block_size; i++) {
            s->get_block_row(src, src_linesize, y + i, x, block_size, bufferh + block_size * i);
            av_dct_calc(sc->dctf, bufferh + block_size * i);
        }

        for (i = 0; i < block_size; i++) {
            for (j = 0; j < block_size; j++) {
                bufferv[i * block_size + j] = bufferh[j * block_size + i];
            }
            av_dct_calc(sc->dctf, bufferv + i * block_size);
        }

        for (i = 0; i < block_size; i++) {
            memcpy(buffer + k * buffer_linesize + i * block_size,
                   bufferv + i * block_size, block_size * 4);
        }
    }

    for (i = 0; i < block_size; i++) {
        for (j = 0; j < block_size; j++) {
            for (k = 0; k < nb_match_blocks; k++)
                bufferz[k] = buffer[buffer_linesize * k + i * block_size + j];
            if (group_size > 1)
                av_dct_calc(sc->gdctf, bufferz);
            bufferz += pgroup_size;
        }
    }

    threshold[0] = s->hard_threshold * s->sigma;
    threshold[1] = threshold[0] * sqrtf(2.f);
    threshold[2] = threshold[0] * 2.f;
    threshold[3] = threshold[0] * sqrtf(8.f);
    bufferz = sc->bufferz;

    for (i = 0; i < block_size; i++) {
        for (j = 0; j < block_size; j++) {
            for (k = 0; k < nb_match_blocks; k++) {
                const float thresh = threshold[(j == 0) + (i == 0) + (k == 0)];

                if (bufferz[k] > thresh || bufferz[k] < -thresh) {
                    retained++;
                } else {
                    bufferz[k] = 0;
                }
            }
            bufferz += pgroup_size;
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

    den_weight = retained < 1 ? 1.f : 1.f / retained;
    num_weight = den_weight;

    buffer = sc->buffer;
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