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
 int /*<<< orphan*/  atomic_sub (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbfs_memory_usage ; 

__attribute__((used)) static void usbfs_decrease_memory_usage(unsigned amount)
{
	atomic_sub(amount, &usbfs_memory_usage);
}