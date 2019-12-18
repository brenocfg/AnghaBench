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
struct os_refcnt {int /*<<< orphan*/  ref_group; scalar_t__ ref_count; } ;
typedef  scalar_t__ os_ref_count_t ;

/* Variables and functions */
 int /*<<< orphan*/  REFLOG_RETAIN ; 
 int /*<<< orphan*/  os_ref_check_retain (struct os_refcnt*,scalar_t__) ; 
 int /*<<< orphan*/  ref_log_op (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_retain_group (int /*<<< orphan*/ ) ; 

void
os_ref_retain_locked(struct os_refcnt *rc)
{
	os_ref_count_t val = rc->ref_count;
	os_ref_check_retain(rc, val);
	rc->ref_count = ++val;

#if OS_REFCNT_DEBUG
	ref_retain_group(rc->ref_group);
	ref_log_op(rc->ref_group, (void *)rc, REFLOG_RETAIN);
#endif
}