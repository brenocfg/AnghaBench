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
struct TYPE_3__ {int mbidx; int /*<<< orphan*/ * mv; int /*<<< orphan*/ * col_mv; } ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 size_t MV_FWD_X0 ; 
 size_t MV_FWD_X1 ; 
 size_t MV_FWD_X2 ; 
 size_t MV_FWD_X3 ; 

__attribute__((used)) static inline void store_mvs(AVSContext *h)
{
    h->col_mv[h->mbidx * 4 + 0] = h->mv[MV_FWD_X0];
    h->col_mv[h->mbidx * 4 + 1] = h->mv[MV_FWD_X1];
    h->col_mv[h->mbidx * 4 + 2] = h->mv[MV_FWD_X2];
    h->col_mv[h->mbidx * 4 + 3] = h->mv[MV_FWD_X3];
}