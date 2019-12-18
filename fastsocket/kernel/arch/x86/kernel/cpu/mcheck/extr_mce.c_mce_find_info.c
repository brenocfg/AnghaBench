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
struct mce_info {scalar_t__ t; int /*<<< orphan*/  inuse; } ;

/* Variables and functions */
 size_t MCE_INFO_MAX ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ current ; 
 struct mce_info* mce_info ; 

__attribute__((used)) static struct mce_info *mce_find_info(void)
{
	struct mce_info *mi;

	for (mi = mce_info; mi < &mce_info[MCE_INFO_MAX]; mi++)
		if (atomic_read(&mi->inuse) && mi->t == current)
			return mi;
	return NULL;
}