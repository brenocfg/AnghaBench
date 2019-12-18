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
struct quota_format_type {struct quota_format_type* qf_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  dq_list_lock ; 
 struct quota_format_type* quota_formats ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void unregister_quota_format(struct quota_format_type *fmt)
{
	struct quota_format_type **actqf;

	spin_lock(&dq_list_lock);
	for (actqf = &quota_formats; *actqf && *actqf != fmt;
	     actqf = &(*actqf)->qf_next)
		;
	if (*actqf)
		*actqf = (*actqf)->qf_next;
	spin_unlock(&dq_list_lock);
}