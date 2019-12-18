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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ sli_intr; scalar_t__ sli_prev_intr; scalar_t__ sli_ips; } ;
struct TYPE_4__ {TYPE_1__ slistat; } ;
struct lpfc_hba {int /*<<< orphan*/  eratt_poll; TYPE_2__ sli; } ;

/* Variables and functions */
 int LPFC_ERATT_POLL_INTERVAL ; 
 scalar_t__ do_div (scalar_t__,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ lpfc_sli_check_eratt (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 

void lpfc_poll_eratt(unsigned long ptr)
{
	struct lpfc_hba *phba;
	uint32_t eratt = 0, rem;
	uint64_t sli_intr, cnt;

	phba = (struct lpfc_hba *)ptr;

	/* Here we will also keep track of interrupts per sec of the hba */
	sli_intr = phba->sli.slistat.sli_intr;

	if (phba->sli.slistat.sli_prev_intr > sli_intr)
		cnt = (((uint64_t)(-1) - phba->sli.slistat.sli_prev_intr) +
			sli_intr);
	else
		cnt = (sli_intr - phba->sli.slistat.sli_prev_intr);

	/* 64-bit integer division not supporte on 32-bit x86 - use do_div */
	rem = do_div(cnt, LPFC_ERATT_POLL_INTERVAL);
	phba->sli.slistat.sli_ips = cnt;

	phba->sli.slistat.sli_prev_intr = sli_intr;

	/* Check chip HA register for error event */
	eratt = lpfc_sli_check_eratt(phba);

	if (eratt)
		/* Tell the worker thread there is work to do */
		lpfc_worker_wake_up(phba);
	else
		/* Restart the timer for next eratt poll */
		mod_timer(&phba->eratt_poll,
			  jiffies +
			  msecs_to_jiffies(1000 * LPFC_ERATT_POLL_INTERVAL));
	return;
}