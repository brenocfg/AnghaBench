#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int cause; scalar_t__ loc; } ;
struct l3_process {TYPE_3__* st; TYPE_1__ para; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_3__*,int,struct l3_process*) ;} ;
struct TYPE_6__ {TYPE_2__ l3; } ;

/* Variables and functions */
 int CC_RELEASE ; 
 int INDICATION ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_l3_process (struct l3_process*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3dss1_dl_release(struct l3_process *pc, u_char pr, void *arg)
{
        newl3state(pc, 0);
        pc->para.cause = 0x1b;          /* Destination out of order */
        pc->para.loc = 0;
        pc->st->l3.l3l4(pc->st, CC_RELEASE | INDICATION, pc);
        release_l3_process(pc);
}