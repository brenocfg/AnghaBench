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
struct TYPE_3__ {int top; int mb_w; int mb_h; int mb_size; int mb_stride; int /*<<< orphan*/  mv; } ;
typedef  TYPE_1__ MVInfo ;
typedef  int /*<<< orphan*/  MV ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvi_reset(MVInfo *mvi, int mb_w, int mb_h, int mb_size)
{
    mvi->top       = 1;
    mvi->mb_w      = mb_w;
    mvi->mb_h      = mb_h;
    mvi->mb_size   = mb_size;
    mvi->mb_stride = mb_w;
    memset(mvi->mv, 0, sizeof(MV) * mvi->mb_stride * 2);
}