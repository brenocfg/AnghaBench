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
struct b43_wldev {struct b43_wl* wl; } ;
struct b43_wl {int beacon0_uploaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_SHM_SH_BTL0 ; 
 int /*<<< orphan*/  B43_SHM_SH_BT_BASE0 ; 
 int /*<<< orphan*/  b43_write_beacon_template (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_upload_beacon0(struct b43_wldev *dev)
{
	struct b43_wl *wl = dev->wl;

	if (wl->beacon0_uploaded)
		return;
	b43_write_beacon_template(dev, B43_SHM_SH_BT_BASE0, B43_SHM_SH_BTL0);
	wl->beacon0_uploaded = true;
}