#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int src_linesize; int ref_linesize; int plane; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * src; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_10__ {int block_step; int* planewidth; int* planeheight; int /*<<< orphan*/  (* block_filtering ) (TYPE_3__*,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/  const*,int const,int,int,int const,int) ;scalar_t__ block_size; TYPE_2__* slices; } ;
struct TYPE_9__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
typedef  TYPE_2__ SliceContext ;
typedef  int /*<<< orphan*/  FFTSample ;
typedef  TYPE_3__ BM3DContext ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  block_matching (TYPE_3__*,int /*<<< orphan*/  const*,int const,int,int,int const,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/  const*,int const,int,int,int const,int) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    BM3DContext *s = ctx->priv;
    SliceContext *sc = &s->slices[jobnr];
    const int block_step = s->block_step;
    ThreadData *td = arg;
    const uint8_t *src = td->src;
    const uint8_t *ref = td->ref;
    const int src_linesize = td->src_linesize;
    const int ref_linesize = td->ref_linesize;
    const int plane = td->plane;
    const int width = s->planewidth[plane];
    const int height = s->planeheight[plane];
    const int block_pos_bottom = FFMAX(0, height - s->block_size);
    const int block_pos_right  = FFMAX(0, width - s->block_size);
    const int slice_start = (((height + block_step - 1) / block_step) * jobnr / nb_jobs) * block_step;
    const int slice_end = (jobnr == nb_jobs - 1) ? block_pos_bottom + block_step :
                          (((height + block_step - 1) / block_step) * (jobnr + 1) / nb_jobs) * block_step;
    int i, j;

    memset(sc->num, 0, width * height * sizeof(FFTSample));
    memset(sc->den, 0, width * height * sizeof(FFTSample));

    for (j = slice_start; j < slice_end; j += block_step) {
        if (j > block_pos_bottom) {
            j = block_pos_bottom;
        }

        for (i = 0; i < block_pos_right + block_step; i += block_step) {
            if (i > block_pos_right) {
                i = block_pos_right;
            }

            block_matching(s, ref, ref_linesize, j, i, plane, jobnr);

            s->block_filtering(s, src, src_linesize,
                               ref, ref_linesize, j, i, plane, jobnr);
        }
    }

    return 0;
}