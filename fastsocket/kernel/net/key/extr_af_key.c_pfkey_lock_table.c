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
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfkey_table_lock ; 
 int /*<<< orphan*/  pfkey_table_users ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void pfkey_lock_table(void)
{
	/* read_lock() synchronizes us to pfkey_table_grab */

	read_lock(&pfkey_table_lock);
	atomic_inc(&pfkey_table_users);
	read_unlock(&pfkey_table_lock);
}