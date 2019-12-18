#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {size_t arg; int /*<<< orphan*/  driver; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ isdn_ctrl ;
struct TYPE_14__ {size_t chan; } ;
typedef  TYPE_4__ capidrv_plci ;
struct TYPE_12__ {int /*<<< orphan*/  (* statcallb ) (TYPE_3__*) ;} ;
struct TYPE_15__ {TYPE_2__ interface; int /*<<< orphan*/  myid; TYPE_1__* bchans; } ;
typedef  TYPE_5__ capidrv_contr ;
struct TYPE_11__ {int /*<<< orphan*/ * contr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_DHUP ; 
 int /*<<< orphan*/  free_plci (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void p0(capidrv_contr * card, capidrv_plci * plci)
{
	isdn_ctrl cmd;

	card->bchans[plci->chan].contr = NULL;
	cmd.command = ISDN_STAT_DHUP;
	cmd.driver = card->myid;
	cmd.arg = plci->chan;
	card->interface.statcallb(&cmd);
	free_plci(card, plci);
}