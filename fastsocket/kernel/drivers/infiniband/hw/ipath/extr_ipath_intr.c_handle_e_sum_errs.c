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
typedef  int u64 ;
struct ipath_devdata {int ipath_flags; } ;
typedef  int ipath_err_t ;

/* Variables and functions */
 int E_SUM_LINK_PKTERRS ; 
 int IPATH_LINKACTIVE ; 
 int /*<<< orphan*/  ipath_dbg (char*,unsigned long long) ; 
 int /*<<< orphan*/  ipath_disarm_senderrbufs (struct ipath_devdata*) ; 

__attribute__((used)) static u64 handle_e_sum_errs(struct ipath_devdata *dd, ipath_err_t errs)
{
	u64 ignore_this_time = 0;

	ipath_disarm_senderrbufs(dd);
	if ((errs & E_SUM_LINK_PKTERRS) &&
	    !(dd->ipath_flags & IPATH_LINKACTIVE)) {
		/*
		 * This can happen when SMA is trying to bring the link
		 * up, but the IB link changes state at the "wrong" time.
		 * The IB logic then complains that the packet isn't
		 * valid.  We don't want to confuse people, so we just
		 * don't print them, except at debug
		 */
		ipath_dbg("Ignoring packet errors %llx, because link not "
			  "ACTIVE\n", (unsigned long long) errs);
		ignore_this_time = errs & E_SUM_LINK_PKTERRS;
	}

	return ignore_this_time;
}