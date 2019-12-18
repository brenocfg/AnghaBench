#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct tomoyo_domain_info {size_t profile; } ;
struct TYPE_2__ {unsigned int* value; } ;

/* Variables and functions */
 size_t const TOMOYO_MAX_CONTROL_INDEX ; 
 size_t const TOMOYO_MAX_PROFILES ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ tomoyo_policy_loaded ; 
 TYPE_1__** tomoyo_profile_ptr ; 

unsigned int tomoyo_check_flags(const struct tomoyo_domain_info *domain,
				const u8 index)
{
	const u8 profile = domain->profile;

	if (WARN_ON(in_interrupt()))
		return 0;
	return tomoyo_policy_loaded && index < TOMOYO_MAX_CONTROL_INDEX
#if TOMOYO_MAX_PROFILES != 256
		&& profile < TOMOYO_MAX_PROFILES
#endif
		&& tomoyo_profile_ptr[profile] ?
		tomoyo_profile_ptr[profile]->value[index] : 0;
}