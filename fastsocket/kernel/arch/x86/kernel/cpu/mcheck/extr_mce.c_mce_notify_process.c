#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mce_info {unsigned long paddr; int /*<<< orphan*/  restartable; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCE_VECTOR ; 
 int MF_ACTION_REQUIRED ; 
 int MF_MUST_KILL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  TIF_MCE_NOTIFY ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_clear_info (struct mce_info*) ; 
 struct mce_info* mce_find_info () ; 
 int /*<<< orphan*/  mce_panic (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memory_failure (unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

void mce_notify_process(void)
{
	unsigned long pfn;
	struct mce_info *mi = mce_find_info();
	int flags = MF_ACTION_REQUIRED;

	if (!mi)
		mce_panic("Lost physical address for unconsumed uncorrectable error", NULL, NULL);
	pfn = mi->paddr >> PAGE_SHIFT;

	clear_thread_flag(TIF_MCE_NOTIFY);

	pr_err("Uncorrected hardware memory error in user-access at %llx",
		 mi->paddr);
	/*
	 * We must call memory_failure() here even if the current process is
	 * doomed. We still need to mark the page as poisoned and alert any
	 * other users of the page.
	 */
	if (!mi->restartable)
		flags |= MF_MUST_KILL;
	if (memory_failure(pfn, MCE_VECTOR, flags) < 0) {
		pr_err("Memory error not recovered");
		force_sig(SIGBUS, current);
	}
	mce_clear_info(mi);
}