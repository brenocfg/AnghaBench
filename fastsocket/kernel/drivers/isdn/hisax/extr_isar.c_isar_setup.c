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
typedef  int u_char ;
struct IsdnCardState {TYPE_3__* bcs; } ;
struct TYPE_4__ {int mml; int dpath; } ;
struct TYPE_5__ {TYPE_1__ isar; } ;
struct TYPE_6__ {int /*<<< orphan*/  tqueue; TYPE_2__ hw; scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ISAR_HIS_DPS1 ; 
 int ISAR_HIS_DPS2 ; 
 int ISAR_HIS_P12CFG ; 
 int /*<<< orphan*/  isar_bh ; 
 int /*<<< orphan*/  modeisar (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendmsg (struct IsdnCardState*,int,int,int,int*) ; 

__attribute__((used)) static void
isar_setup(struct IsdnCardState *cs)
{
	u_char msg;
	int i;
	
	/* Dpath 1, 2 */
	msg = 61;
	for (i=0; i<2; i++) {
		/* Buffer Config */
		sendmsg(cs, (i ? ISAR_HIS_DPS2 : ISAR_HIS_DPS1) |
			ISAR_HIS_P12CFG, 4, 1, &msg);
		cs->bcs[i].hw.isar.mml = msg;
		cs->bcs[i].mode = 0;
		cs->bcs[i].hw.isar.dpath = i + 1;
		modeisar(&cs->bcs[i], 0, 0);
		INIT_WORK(&cs->bcs[i].tqueue, isar_bh);
	}
}