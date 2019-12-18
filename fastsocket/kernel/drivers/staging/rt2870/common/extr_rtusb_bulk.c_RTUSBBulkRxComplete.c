#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
typedef  TYPE_1__* purbb_t ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {unsigned long data; } ;
struct TYPE_10__ {TYPE_5__ rx_done_task; } ;
struct TYPE_9__ {scalar_t__ OS_Cookie; } ;
struct TYPE_8__ {TYPE_3__* pAd; } ;
struct TYPE_7__ {scalar_t__ context; } ;
typedef  TYPE_2__* PRX_CONTEXT ;
typedef  TYPE_3__* PRTMP_ADAPTER ;
typedef  TYPE_4__* POS_COOKIE ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_hi_schedule (TYPE_5__*) ; 

VOID RTUSBBulkRxComplete(purbb_t pUrb, struct pt_regs *pt_regs)
{
	// use a receive tasklet to handle received packets;
	// or sometimes hardware IRQ will be disabled here, so we can not
	// use spin_lock_bh()/spin_unlock_bh() after IRQ is disabled. :<
	PRX_CONTEXT		pRxContext;
	PRTMP_ADAPTER	pAd;
	POS_COOKIE 		pObj;


	pRxContext	= (PRX_CONTEXT)pUrb->context;
	pAd 		= pRxContext->pAd;
	pObj 		= (POS_COOKIE) pAd->OS_Cookie;

	pObj->rx_done_task.data = (unsigned long)pUrb;
	tasklet_hi_schedule(&pObj->rx_done_task);

}