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
typedef  int /*<<< orphan*/ * host_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/ * HOST_PRIV_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NOT_SUPPORTED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atm_set_diagnostic_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realhost ; 

kern_return_t
host_set_atm_diagnostic_flag(host_priv_t host_priv, uint32_t diagnostic_flag)
{
	if (host_priv == HOST_PRIV_NULL)
		return (KERN_INVALID_ARGUMENT);

	assert(host_priv == &realhost);

#if CONFIG_ATM
	return (atm_set_diagnostic_config(diagnostic_flag));
#else
	(void)diagnostic_flag;
	return (KERN_NOT_SUPPORTED);
#endif
}