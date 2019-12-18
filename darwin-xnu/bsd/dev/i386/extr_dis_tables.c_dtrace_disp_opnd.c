#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* d86_opnd; } ;
typedef  TYPE_2__ dis86_t ;
struct TYPE_5__ {int /*<<< orphan*/  d86_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_IPREL ; 
 int /*<<< orphan*/  dtrace_imm_opnd (TYPE_2__*,int,int,int) ; 

__attribute__((used)) static void
dtrace_disp_opnd(dis86_t *x, int wbit, int size, int opindex)
{
	dtrace_imm_opnd(x, wbit, size, opindex);
#ifdef DIS_TEXT
	x->d86_opnd[opindex].d86_mode = MODE_IPREL;
#endif
}