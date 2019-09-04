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
 int HOST_LAST_SPECIAL_KERNEL_PORT ; 
 int HOST_MAX_SPECIAL_KERNEL_PORT ; 
 int HOST_MAX_SPECIAL_PORT ; 
 int HOST_MIN_SPECIAL_PORT ; 

__attribute__((used)) static bool
is_valid_host_special_port(int id)
{
	return (id <= HOST_MAX_SPECIAL_PORT) &&
	       (id >= HOST_MIN_SPECIAL_PORT) &&
	       ((id <= HOST_LAST_SPECIAL_KERNEL_PORT) || (id > HOST_MAX_SPECIAL_KERNEL_PORT));
}