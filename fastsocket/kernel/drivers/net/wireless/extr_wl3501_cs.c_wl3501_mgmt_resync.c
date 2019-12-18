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
struct wl3501_resync_req {int /*<<< orphan*/  sig_id; } ;
struct wl3501_card {int dummy; } ;
typedef  int /*<<< orphan*/  sig ;

/* Variables and functions */
 int /*<<< orphan*/  WL3501_SIG_RESYNC_REQ ; 
 int wl3501_esbq_exec (struct wl3501_card*,struct wl3501_resync_req*,int) ; 

__attribute__((used)) static int wl3501_mgmt_resync(struct wl3501_card *this)
{
	struct wl3501_resync_req sig = {
		.sig_id = WL3501_SIG_RESYNC_REQ,
	};

	return wl3501_esbq_exec(this, &sig, sizeof(sig));
}