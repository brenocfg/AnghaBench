#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int group_size; float th_mse; TYPE_2__* slices; } ;
struct TYPE_7__ {int nb_match_blocks; TYPE_1__* match_blocks; } ;
struct TYPE_6__ {int score; int x; int y; } ;
typedef  TYPE_2__ SliceContext ;
typedef  TYPE_3__ BM3DContext ;

/* Variables and functions */
 int /*<<< orphan*/  block_matching_multi (TYPE_3__*,int /*<<< orphan*/  const*,int,int,int,int,int,int) ; 

__attribute__((used)) static void block_matching(BM3DContext *s, const uint8_t *ref, int ref_linesize,
                           int j, int i, int plane, int jobnr)
{
    SliceContext *sc = &s->slices[jobnr];

    if (s->group_size == 1 || s->th_mse <= 0.f) {
        sc->match_blocks[0].score = 1;
        sc->match_blocks[0].x = i;
        sc->match_blocks[0].y = j;
        sc->nb_match_blocks = 1;
        return;
    }

    sc->nb_match_blocks = 0;
    block_matching_multi(s, ref, ref_linesize, j, i, 1, plane, jobnr);
}