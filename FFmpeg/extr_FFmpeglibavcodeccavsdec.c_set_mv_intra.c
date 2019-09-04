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
struct TYPE_6__ {TYPE_1__* f; } ;
struct TYPE_7__ {size_t mbidx; int /*<<< orphan*/ * col_type_base; TYPE_2__ cur; void** mv; } ;
struct TYPE_5__ {scalar_t__ pict_type; } ;
typedef  TYPE_3__ AVSContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int /*<<< orphan*/  BLK_16X16 ; 
 int /*<<< orphan*/  I_8X8 ; 
 size_t MV_BWD_X0 ; 
 size_t MV_FWD_X0 ; 
 void* ff_cavs_intra_mv ; 
 int /*<<< orphan*/  set_mvs (void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_mv_intra(AVSContext *h)
{
    h->mv[MV_FWD_X0] = ff_cavs_intra_mv;
    set_mvs(&h->mv[MV_FWD_X0], BLK_16X16);
    h->mv[MV_BWD_X0] = ff_cavs_intra_mv;
    set_mvs(&h->mv[MV_BWD_X0], BLK_16X16);
    if (h->cur.f->pict_type != AV_PICTURE_TYPE_B)
        h->col_type_base[h->mbidx] = I_8X8;
}