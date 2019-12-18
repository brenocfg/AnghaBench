#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum compressor_preselect_t { ____Placeholder_compressor_preselect_t } compressor_preselect_t ;
struct TYPE_4__ {scalar_t__ lz4_failure_skips; scalar_t__ lz4_failure_run_length; scalar_t__ lz4_preselects; scalar_t__ lz4_run_length; int /*<<< orphan*/  lz4_total_preselects; int /*<<< orphan*/  lz4_total_failure_skips; } ;
struct TYPE_3__ {scalar_t__ lz4_max_failure_skips; scalar_t__ lz4_max_failure_run_length; scalar_t__ lz4_max_preselects; scalar_t__ lz4_run_preselection_threshold; } ;

/* Variables and functions */
 int CPRESELLZ4 ; 
 int CPRESELWK ; 
 int CSKIPLZ4 ; 
 TYPE_2__ vmcstate ; 
 TYPE_1__ vmctune ; 

__attribute__((used)) static inline enum compressor_preselect_t compressor_preselect(void) {
	if (vmcstate.lz4_failure_skips >= vmctune.lz4_max_failure_skips) {
		vmcstate.lz4_failure_skips = 0;
		vmcstate.lz4_failure_run_length = 0;
	}

	if (vmcstate.lz4_failure_run_length >= vmctune.lz4_max_failure_run_length) {
		vmcstate.lz4_failure_skips++;
		vmcstate.lz4_total_failure_skips++;
		return CSKIPLZ4;
	}

	if (vmcstate.lz4_preselects >= vmctune.lz4_max_preselects) {
		vmcstate.lz4_preselects = 0;
		return CPRESELWK;
	}

	if (vmcstate.lz4_run_length >= vmctune.lz4_run_preselection_threshold) {
		vmcstate.lz4_preselects++;
		vmcstate.lz4_total_preselects++;
		return CPRESELLZ4;
	}
	return CPRESELWK;
}