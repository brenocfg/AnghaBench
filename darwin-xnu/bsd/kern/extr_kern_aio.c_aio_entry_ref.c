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
typedef  int /*<<< orphan*/  aio_workq_entry ;

/* Variables and functions */
 int /*<<< orphan*/  aio_entry_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aio_entry_ref_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aio_entry_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void	
aio_entry_ref(aio_workq_entry *entryp)
{
	aio_entry_lock_spin(entryp);
	aio_entry_ref_locked(entryp);
	aio_entry_unlock(entryp);
}