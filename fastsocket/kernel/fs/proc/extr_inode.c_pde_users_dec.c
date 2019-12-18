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
struct proc_dir_entry {int /*<<< orphan*/  pde_unload_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pde_users_dec (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pde_users_dec(struct proc_dir_entry *pde)
{
	spin_lock(&pde->pde_unload_lock);
	__pde_users_dec(pde);
	spin_unlock(&pde->pde_unload_lock);
}