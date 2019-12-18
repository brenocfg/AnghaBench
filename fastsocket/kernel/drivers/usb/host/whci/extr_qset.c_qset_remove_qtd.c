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
struct whc_qset {size_t td_start; int /*<<< orphan*/  ntds; TYPE_1__* qtd; } ;
struct whc {int dummy; } ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */
 size_t WHCI_QSET_TD_MAX ; 

__attribute__((used)) static void qset_remove_qtd(struct whc *whc, struct whc_qset *qset)
{
	qset->qtd[qset->td_start].status = 0;

	if (++qset->td_start >= WHCI_QSET_TD_MAX)
		qset->td_start = 0;
	qset->ntds--;
}