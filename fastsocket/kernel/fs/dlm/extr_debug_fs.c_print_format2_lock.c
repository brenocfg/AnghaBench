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
typedef  scalar_t__ u64 ;
struct seq_file {int dummy; } ;
struct dlm_rsb {int /*<<< orphan*/  res_name; int /*<<< orphan*/  res_length; int /*<<< orphan*/  res_nodeid; } ;
struct dlm_lkb {int lkb_flags; int /*<<< orphan*/  lkb_rqmode; int /*<<< orphan*/  lkb_grmode; int /*<<< orphan*/  lkb_status; int /*<<< orphan*/  lkb_exflags; int /*<<< orphan*/  lkb_ownpid; int /*<<< orphan*/  lkb_remid; int /*<<< orphan*/  lkb_nodeid; int /*<<< orphan*/  lkb_id; int /*<<< orphan*/  lkb_timestamp; TYPE_1__* lkb_ua; } ;
struct TYPE_2__ {scalar_t__ xid; } ;

/* Variables and functions */
 int DLM_IFL_USER ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int print_format2_lock(struct seq_file *s, struct dlm_lkb *lkb,
			      struct dlm_rsb *r)
{
	u64 xid = 0;
	u64 us;
	int rv;

	if (lkb->lkb_flags & DLM_IFL_USER) {
		if (lkb->lkb_ua)
			xid = lkb->lkb_ua->xid;
	}

	/* microseconds since lkb was added to current queue */
	us = ktime_to_us(ktime_sub(ktime_get(), lkb->lkb_timestamp));

	/* id nodeid remid pid xid exflags flags sts grmode rqmode time_us
	   r_nodeid r_len r_name */

	rv = seq_printf(s, "%x %d %x %u %llu %x %x %d %d %d %llu %u %d \"%s\"\n",
			lkb->lkb_id,
			lkb->lkb_nodeid,
			lkb->lkb_remid,
			lkb->lkb_ownpid,
			(unsigned long long)xid,
			lkb->lkb_exflags,
			lkb->lkb_flags,
			lkb->lkb_status,
			lkb->lkb_grmode,
			lkb->lkb_rqmode,
			(unsigned long long)us,
			r->res_nodeid,
			r->res_length,
			r->res_name);
	return rv;
}