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
struct mce {int bank; int status; scalar_t__ tsc; scalar_t__ addr; scalar_t__ misc; } ;
typedef  int /*<<< orphan*/  mce_banks_t ;
typedef  enum mcp_flags { ____Placeholder_mcp_flags } mcp_flags ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int MCI_STATUS_S ; 
 int MCI_STATUS_UC ; 
 int MCI_STATUS_VAL ; 
 int MCP_DONTLOG ; 
 int MCP_TIMESTAMP ; 
 int MCP_UC ; 
 int /*<<< orphan*/  MSR_IA32_MCx_STATUS (int) ; 
 int banks ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_1__* mce_banks ; 
 int /*<<< orphan*/  mce_dont_log_ce ; 
 int /*<<< orphan*/  mce_gather_info (struct mce*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_log (struct mce*) ; 
 int /*<<< orphan*/  mce_poll_count ; 
 scalar_t__ mce_quirk (int,struct mce*) ; 
 int mce_rdmsrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_read_aux (struct mce*,int) ; 
 scalar_t__ mce_ser ; 
 int /*<<< orphan*/  mce_wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_core () ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

void machine_check_poll(enum mcp_flags flags, mce_banks_t *b)
{
	struct mce m;
	int i;

	percpu_inc(mce_poll_count);

	mce_gather_info(&m, NULL);

	for (i = 0; i < banks; i++) {
		if (!mce_banks[i].ctl || !test_bit(i, *b))
			continue;

		m.misc = 0;
		m.addr = 0;
		m.bank = i;
		m.tsc = 0;

		barrier();
		m.status = mce_rdmsrl(MSR_IA32_MCx_STATUS(i));
		if (!(m.status & MCI_STATUS_VAL))
			continue;

		if (mce_quirk(i, &m))
			continue;

		/*
		 * Uncorrected or signalled events are handled by the exception
		 * handler when it is enabled, so don't process those here.
		 *
		 * TBD do the same check for MCI_STATUS_EN here?
		 */
		if (!(flags & MCP_UC) &&
		    (m.status & (mce_ser ? MCI_STATUS_S : MCI_STATUS_UC)))
			continue;

		mce_read_aux(&m, i);

		if (!(flags & MCP_TIMESTAMP))
			m.tsc = 0;
		/*
		 * Don't get the IP here because it's unlikely to
		 * have anything to do with the actual error location.
		 */
		if (!(flags & MCP_DONTLOG) && !mce_dont_log_ce)
			mce_log(&m);

		/*
		 * Clear state for this bank.
		 */
		mce_wrmsrl(MSR_IA32_MCx_STATUS(i), 0);
	}

	/*
	 * Don't clear MCG_STATUS here because it's only defined for
	 * exceptions.
	 */

	sync_core();
}