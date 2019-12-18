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
struct ubifs_info {int /*<<< orphan*/  space_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 long long ubifs_get_free_space_nolock (struct ubifs_info*) ; 

long long ubifs_get_free_space(struct ubifs_info *c)
{
	long long free;

	spin_lock(&c->space_lock);
	free = ubifs_get_free_space_nolock(c);
	spin_unlock(&c->space_lock);

	return free;
}