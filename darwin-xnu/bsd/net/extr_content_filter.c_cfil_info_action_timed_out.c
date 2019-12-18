#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; } ;
struct TYPE_7__ {scalar_t__ cfi_pending_last; scalar_t__ cfi_pass_offset; } ;
struct TYPE_5__ {scalar_t__ cfi_pending_last; scalar_t__ cfi_pass_offset; } ;
struct cfil_info {TYPE_3__ cfi_rcv; TYPE_1__ cfi_snd; struct cfil_entry* cfi_entries; } ;
struct TYPE_8__ {scalar_t__ cfe_pass_offset; } ;
struct TYPE_6__ {scalar_t__ cfe_pass_offset; } ;
struct cfil_entry {int /*<<< orphan*/  cfe_last_action; TYPE_4__ cfe_rcv; TYPE_2__ cfe_snd; int /*<<< orphan*/ * cfe_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int MAX_CONTENT_FILTER ; 
 int /*<<< orphan*/  cfil_info_log (int /*<<< orphan*/ ,struct cfil_info*,char*) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 int /*<<< orphan*/  timersub (struct timeval*,int /*<<< orphan*/ *,struct timeval*) ; 

bool
cfil_info_action_timed_out(struct cfil_info *cfil_info, int timeout)
{
	struct cfil_entry *entry;
	struct timeval current_tv;
	struct timeval diff_time;

	if (cfil_info == NULL)
		return false;

	/*
	 * If we have queued up more data than passed offset and we haven't received
	 * an action from user space for a while (the user space filter might have crashed),
	 * return action timed out.
	 */
	if (cfil_info->cfi_snd.cfi_pending_last > cfil_info->cfi_snd.cfi_pass_offset ||
		cfil_info->cfi_rcv.cfi_pending_last > cfil_info->cfi_rcv.cfi_pass_offset) {

		microuptime(&current_tv);

		for (int kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
			entry = &cfil_info->cfi_entries[kcunit - 1];

			if (entry->cfe_filter == NULL)
				continue;

			if (cfil_info->cfi_snd.cfi_pending_last > entry->cfe_snd.cfe_pass_offset ||
				cfil_info->cfi_rcv.cfi_pending_last > entry->cfe_rcv.cfe_pass_offset) {
				// haven't gotten an action from this filter, check timeout
				timersub(&current_tv, &entry->cfe_last_action, &diff_time);
				if (diff_time.tv_sec >= timeout) {
#if GC_DEBUG
					cfil_info_log(LOG_ERR, cfil_info, "CFIL: flow ACTION timeout expired");
#endif
					return true;
				}
			}
		}
	}
	return false;
}