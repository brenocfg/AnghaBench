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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hibernate_vm_locks_safe ; 
 scalar_t__ ml_get_interrupts_enabled () ; 

boolean_t
hibernate_vm_locks_are_safe(void)
{
    assert(FALSE == ml_get_interrupts_enabled());
    return (hibernate_vm_locks_safe);
}