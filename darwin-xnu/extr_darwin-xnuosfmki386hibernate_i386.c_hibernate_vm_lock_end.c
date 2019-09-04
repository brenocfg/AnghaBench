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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ hibernate_vm_locks_safe ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  ml_set_is_quiescing (scalar_t__) ; 

void
hibernate_vm_lock_end(void)
{
    assert(FALSE == ml_get_interrupts_enabled());
    hibernate_vm_locks_safe = FALSE;
    ml_set_is_quiescing(FALSE);
}