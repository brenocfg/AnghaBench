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
struct pvr2_hdw {void (* state_func ) (void*) ;int flag_init_ok; int /*<<< orphan*/  big_lock; void* state_data; scalar_t__ flag_disconnected; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_hdw_setup (struct pvr2_hdw*) ; 

int pvr2_hdw_initialize(struct pvr2_hdw *hdw,
			void (*callback_func)(void *),
			void *callback_data)
{
	LOCK_TAKE(hdw->big_lock); do {
		if (hdw->flag_disconnected) {
			/* Handle a race here: If we're already
			   disconnected by this point, then give up.  If we
			   get past this then we'll remain connected for
			   the duration of initialization since the entire
			   initialization sequence is now protected by the
			   big_lock. */
			break;
		}
		hdw->state_data = callback_data;
		hdw->state_func = callback_func;
		pvr2_hdw_setup(hdw);
	} while (0); LOCK_GIVE(hdw->big_lock);
	return hdw->flag_init_ok;
}