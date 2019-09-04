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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  host_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOT_SUPPORTED ; 

kern_return_t
host_set_multiuser_config_flags(host_priv_t host_priv, uint32_t multiuser_config)
{
#if CONFIG_EMBEDDED
	if (host_priv == HOST_PRIV_NULL)
		return (KERN_INVALID_ARGUMENT);

	assert(host_priv == &realhost);

	/*
	 * Always enforce that the multiuser bit is set
	 * if a value is written to the commpage word.
	 */
	commpage_update_multiuser_config(multiuser_config | kIsMultiUserDevice);
	return (KERN_SUCCESS);
#else
	(void)host_priv;
	(void)multiuser_config;
	return (KERN_NOT_SUPPORTED);
#endif
}