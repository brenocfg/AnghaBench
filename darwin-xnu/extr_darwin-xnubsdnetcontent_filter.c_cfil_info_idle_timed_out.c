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
typedef  scalar_t__ u_int32_t ;
struct cfil_info {TYPE_1__* cfi_hash_entry; } ;
struct TYPE_2__ {scalar_t__ cfentry_lastused; } ;

/* Variables and functions */

bool
cfil_info_idle_timed_out(struct cfil_info *cfil_info, int timeout, u_int32_t current_time)
{
	if (cfil_info && cfil_info->cfi_hash_entry &&
		(current_time - cfil_info->cfi_hash_entry->cfentry_lastused >= (u_int32_t)timeout)) {
#if GC_DEBUG
		cfil_info_log(LOG_ERR, cfil_info, "CFIL: flow IDLE timeout expired");
#endif
		return true;
	}
	return false;
}