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
typedef  int /*<<< orphan*/  u16 ;
struct wl3501_card {int dummy; } ;
struct wl3501_auth_confirm {scalar_t__ status; } ;
typedef  int /*<<< orphan*/  sig ;

/* Variables and functions */
 scalar_t__ WL3501_STATUS_SUCCESS ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  wl3501_get_from_wla (struct wl3501_card*,int /*<<< orphan*/ ,struct wl3501_auth_confirm*,int) ; 
 int /*<<< orphan*/  wl3501_mgmt_association (struct wl3501_card*) ; 
 int /*<<< orphan*/  wl3501_mgmt_resync (struct wl3501_card*) ; 

__attribute__((used)) static inline void wl3501_auth_confirm_interrupt(struct wl3501_card *this,
						 u16 addr)
{
	struct wl3501_auth_confirm sig;

	dprintk(3, "entry");
	wl3501_get_from_wla(this, addr, &sig, sizeof(sig));

	if (sig.status == WL3501_STATUS_SUCCESS)
		wl3501_mgmt_association(this);
	else
		wl3501_mgmt_resync(this);
}