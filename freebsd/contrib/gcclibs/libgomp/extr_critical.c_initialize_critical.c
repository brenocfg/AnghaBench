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
 int /*<<< orphan*/  atomic_lock ; 
 int /*<<< orphan*/  create_lock_lock ; 
 int /*<<< orphan*/  default_lock ; 
 int /*<<< orphan*/  gomp_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __attribute__((constructor))
initialize_critical (void)
{
  gomp_mutex_init (&default_lock);
  gomp_mutex_init (&atomic_lock);
#ifndef HAVE_SYNC_BUILTINS
  gomp_mutex_init (&create_lock_lock);
#endif
}