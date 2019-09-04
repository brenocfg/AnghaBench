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
struct TYPE_11__ {int* planewidth; int* planeheight; int block_size; int bm_step; int const bm_range; int /*<<< orphan*/  th_mse; TYPE_2__* slices; } ;
struct TYPE_10__ {int y; int x; } ;
struct TYPE_9__ {int nb_match_blocks; TYPE_3__* search_positions; TYPE_1__* match_blocks; } ;
struct TYPE_8__ {int y; int x; scalar_t__ score; } ;
typedef  TYPE_2__ SliceContext ;
typedef  TYPE_3__ PosCode ;
typedef  TYPE_4__ BM3DContext ;

/* Variables and functions */
 int /*<<< orphan*/  do_block_matching_multi (TYPE_4__*,int /*<<< orphan*/  const*,int,int const,TYPE_3__*,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int search_boundary (int const,int const,int const,int,int,int) ; 

__attribute__((used)) static void block_matching_multi(BM3DContext *s, const uint8_t *ref, int ref_linesize, int y, int x,
                                 int exclude_cur_pos, int plane, int jobnr)
{
    SliceContext *sc = &s->slices[jobnr];
    const int width = s->planewidth[plane];
    const int height = s->planeheight[plane];
    const int block_size = s->block_size;
    const int step = s->bm_step;
    const int range = s->bm_range / step * step;
    int l = search_boundary(0, range, step, 0, y, x);
    int r = search_boundary(width - block_size, range, step, 0, y, x);
    int t = search_boundary(0, range, step, 1, y, x);
    int b = search_boundary(height - block_size, range, step, 1, y, x);
    int j, i, index = 0;

    for (j = t; j <= b; j += step) {
        for (i = l; i <= r; i += step) {
            PosCode pos;

            if (exclude_cur_pos > 0 && j == y && i == x) {
                continue;
            }

            pos.y = j;
            pos.x = i;
            sc->search_positions[index++] = pos;
        }
    }

    if (exclude_cur_pos == 1) {
        sc->match_blocks[0].score = 0;
        sc->match_blocks[0].y = y;
        sc->match_blocks[0].x = x;
        sc->nb_match_blocks = 1;
    }

    do_block_matching_multi(s, ref, ref_linesize, s->bm_range,
                            sc->search_positions, index, s->th_mse, y, x, plane, jobnr);
}