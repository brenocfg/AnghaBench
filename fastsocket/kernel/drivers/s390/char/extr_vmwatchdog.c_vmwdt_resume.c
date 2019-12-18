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
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  VMWDT_OPEN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmwdt_is_open ; 

__attribute__((used)) static int vmwdt_resume(void)
{
	clear_bit(VMWDT_OPEN, &vmwdt_is_open);
	return NOTIFY_DONE;
}