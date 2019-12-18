#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct isar_hw {TYPE_2__* ch; } ;
struct TYPE_3__ {scalar_t__ state; } ;
struct TYPE_4__ {int mml; int dpath; TYPE_1__ bch; } ;

/* Variables and functions */
 int ISAR_HIS_DPS1 ; 
 int ISAR_HIS_DPS2 ; 
 int ISAR_HIS_P12CFG ; 
 int /*<<< orphan*/  ISDN_P_NONE ; 
 int /*<<< orphan*/  modeisar (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_mbox (struct isar_hw*,int,int,int,int*) ; 

__attribute__((used)) static void
isar_setup(struct isar_hw *isar)
{
	u8 msg;
	int i;

	/* Dpath 1, 2 */
	msg = 61;
	for (i = 0; i < 2; i++) {
		/* Buffer Config */
		send_mbox(isar, (i ? ISAR_HIS_DPS2 : ISAR_HIS_DPS1) |
			ISAR_HIS_P12CFG, 4, 1, &msg);
		isar->ch[i].mml = msg;
		isar->ch[i].bch.state = 0;
		isar->ch[i].dpath = i + 1;
		modeisar(&isar->ch[i], ISDN_P_NONE);
	}
}