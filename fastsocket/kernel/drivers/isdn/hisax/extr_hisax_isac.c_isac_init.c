#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int debug; int /*<<< orphan*/  printdebug; struct isac* userdata; int /*<<< orphan*/  state; int /*<<< orphan*/ * fsm; } ;
struct isac {int /*<<< orphan*/  timer; TYPE_1__ l1m; int /*<<< orphan*/ * tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmInitTimer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_L1_RESET ; 
 int /*<<< orphan*/  l1fsm ; 
 int /*<<< orphan*/  l1m_debug ; 

void isac_init(struct isac *isac)
{
	isac->tx_skb = NULL;
	isac->l1m.fsm = &l1fsm;
	isac->l1m.state = ST_L1_RESET;
#ifdef CONFIG_HISAX_DEBUG
	isac->l1m.debug = 1;
#else
	isac->l1m.debug = 0;
#endif
	isac->l1m.userdata = isac;
	isac->l1m.printdebug = l1m_debug;
	FsmInitTimer(&isac->l1m, &isac->timer);
}