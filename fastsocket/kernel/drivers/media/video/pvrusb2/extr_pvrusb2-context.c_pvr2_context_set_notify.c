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
struct pvr2_context {int notify_flag; struct pvr2_context* notify_next; struct pvr2_context* notify_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_context_mutex ; 
 struct pvr2_context* pvr2_context_notify_first ; 
 struct pvr2_context* pvr2_context_notify_last ; 
 int /*<<< orphan*/  pvr2_context_sync_data ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvr2_context_set_notify(struct pvr2_context *mp, int fl)
{
	int signal_flag = 0;
	mutex_lock(&pvr2_context_mutex);
	if (fl) {
		if (!mp->notify_flag) {
			signal_flag = (pvr2_context_notify_first == NULL);
			mp->notify_prev = pvr2_context_notify_last;
			mp->notify_next = NULL;
			pvr2_context_notify_last = mp;
			if (mp->notify_prev) {
				mp->notify_prev->notify_next = mp;
			} else {
				pvr2_context_notify_first = mp;
			}
			mp->notify_flag = !0;
		}
	} else {
		if (mp->notify_flag) {
			mp->notify_flag = 0;
			if (mp->notify_next) {
				mp->notify_next->notify_prev = mp->notify_prev;
			} else {
				pvr2_context_notify_last = mp->notify_prev;
			}
			if (mp->notify_prev) {
				mp->notify_prev->notify_next = mp->notify_next;
			} else {
				pvr2_context_notify_first = mp->notify_next;
			}
		}
	}
	mutex_unlock(&pvr2_context_mutex);
	if (signal_flag) wake_up(&pvr2_context_sync_data);
}