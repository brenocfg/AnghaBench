#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  driver; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ isdn_ctrl ;
struct TYPE_19__ {int /*<<< orphan*/  chan; TYPE_9__* plcip; } ;
typedef  TYPE_4__ capidrv_ncci ;
struct TYPE_16__ {int /*<<< orphan*/  (* statcallb ) (TYPE_3__*) ;} ;
struct TYPE_20__ {TYPE_1__ interface; int /*<<< orphan*/  myid; int /*<<< orphan*/  msgid; } ;
typedef  TYPE_5__ capidrv_contr ;
struct TYPE_21__ {int /*<<< orphan*/  plci; } ;
struct TYPE_17__ {int /*<<< orphan*/  applid; } ;
struct TYPE_15__ {TYPE_2__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_PLCI_DISCONNECT_REQ ; 
 int /*<<< orphan*/  ISDN_STAT_BHUP ; 
 int /*<<< orphan*/  capi_fill_DISCONNECT_REQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsg ; 
 int /*<<< orphan*/  free_ncci (TYPE_5__*,TYPE_4__*) ; 
 TYPE_12__ global ; 
 int /*<<< orphan*/  plci_change_state (TYPE_5__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_message (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void n0(capidrv_contr * card, capidrv_ncci * ncci)
{
	isdn_ctrl cmd;

	capi_fill_DISCONNECT_REQ(&cmsg,
				 global.ap.applid,
				 card->msgid++,
				 ncci->plcip->plci,
				 NULL,	/* BChannelinformation */
				 NULL,	/* Keypadfacility */
				 NULL,	/* Useruserdata */   /* $$$$ */
				 NULL	/* Facilitydataarray */
	);
	plci_change_state(card, ncci->plcip, EV_PLCI_DISCONNECT_REQ);
	send_message(card, &cmsg);

	cmd.command = ISDN_STAT_BHUP;
	cmd.driver = card->myid;
	cmd.arg = ncci->chan;
	card->interface.statcallb(&cmd);
	free_ncci(card, ncci);
}