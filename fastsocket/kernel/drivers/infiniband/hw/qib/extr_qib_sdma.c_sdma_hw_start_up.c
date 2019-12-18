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
struct qib_sdma_state {unsigned int first_sendbuf; unsigned int last_sendbuf; } ;
struct qib_pportdata {TYPE_1__* dd; struct qib_sdma_state sdma_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* f_sdma_hw_start_up ) (struct qib_pportdata*) ;int /*<<< orphan*/  (* f_sendctrl ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_SENDCTRL_DISARM_BUF (unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct qib_pportdata*) ; 

__attribute__((used)) static void sdma_hw_start_up(struct qib_pportdata *ppd)
{
	struct qib_sdma_state *ss = &ppd->sdma_state;
	unsigned bufno;

	for (bufno = ss->first_sendbuf; bufno < ss->last_sendbuf; ++bufno)
		ppd->dd->f_sendctrl(ppd, QIB_SENDCTRL_DISARM_BUF(bufno));

	ppd->dd->f_sdma_hw_start_up(ppd);
}