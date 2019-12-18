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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  create_workqueue (char*) ; 
 int /*<<< orphan*/  ocfs2_quota_wq ; 

int ocfs2_quota_setup(void)
{
	ocfs2_quota_wq = create_workqueue("o2quot");
	if (!ocfs2_quota_wq)
		return -ENOMEM;
	return 0;
}