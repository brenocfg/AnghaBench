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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  fdisables ;
typedef  int boolean_t ;

/* Variables and functions */
 int KF_INITIALIZED ; 
 scalar_t__ PE_parse_boot_argn (char*,int*,int) ; 
 int kern_feature_overrides ; 

boolean_t kern_feature_override(uint32_t fmask) {
	if (kern_feature_overrides == 0) {
		uint32_t fdisables = 0;
		/* Expected to be first invoked early, in a single-threaded
		 * environment
		 */
		if (PE_parse_boot_argn("validation_disables", &fdisables, sizeof(fdisables))) {
			fdisables |= KF_INITIALIZED;
			kern_feature_overrides = fdisables;
		} else {
			kern_feature_overrides |= KF_INITIALIZED;
		}
	}
	return ((kern_feature_overrides & fmask) == fmask);
}