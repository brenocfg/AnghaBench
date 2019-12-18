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
 int /*<<< orphan*/  adapter_lock ; 
 int /*<<< orphan*/  diva_os_initialize_spin_lock (int /*<<< orphan*/ *,char*) ; 

int diva_user_mode_idi_init(void)
{
	diva_os_initialize_spin_lock(&adapter_lock, "adapter");
	return (0);
}