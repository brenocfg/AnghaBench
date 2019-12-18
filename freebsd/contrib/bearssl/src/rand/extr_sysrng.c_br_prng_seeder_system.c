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
typedef  int /*<<< orphan*/ * br_prng_seeder ;

/* Variables and functions */
 scalar_t__ rdrand_supported () ; 
 int /*<<< orphan*/  seeder_rdrand ; 
 int /*<<< orphan*/  seeder_urandom ; 
 int /*<<< orphan*/  seeder_win32 ; 

br_prng_seeder
br_prng_seeder_system(const char **name)
{
#if BR_RDRAND
	if (rdrand_supported()) {
		if (name != NULL) {
			*name = "rdrand";
		}
		return &seeder_rdrand;
	}
#endif
#if BR_USE_URANDOM
	if (name != NULL) {
		*name = "urandom";
	}
	return &seeder_urandom;
#elif BR_USE_WIN32_RAND
	if (name != NULL) {
		*name = "win32";
	}
	return &seeder_win32;
#else
	if (name != NULL) {
		*name = "none";
	}
	return 0;
#endif
}