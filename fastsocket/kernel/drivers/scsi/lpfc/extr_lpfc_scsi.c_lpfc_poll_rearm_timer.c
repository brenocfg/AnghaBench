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
struct TYPE_4__ {TYPE_1__* ring; } ;
struct lpfc_hba {int /*<<< orphan*/  fcp_poll_timer; TYPE_2__ sli; int /*<<< orphan*/  cfg_poll_tmo; } ;
struct TYPE_3__ {int /*<<< orphan*/  txcmplq; } ;

/* Variables and functions */
 size_t LPFC_FCP_RING ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void lpfc_poll_rearm_timer(struct lpfc_hba * phba)
{
	unsigned long  poll_tmo_expires =
		(jiffies + msecs_to_jiffies(phba->cfg_poll_tmo));

	if (!list_empty(&phba->sli.ring[LPFC_FCP_RING].txcmplq))
		mod_timer(&phba->fcp_poll_timer,
			  poll_tmo_expires);
}