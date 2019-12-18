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
typedef  int /*<<< orphan*/  u8 ;
struct wl1271_acx_inconnection_sta {int /*<<< orphan*/  addr; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_UPDATE_INCONNECTION_STA_LIST ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_inconnection_sta*) ; 
 struct wl1271_acx_inconnection_sta* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_inconnection_sta*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_set_inconnection_sta(struct wl1271 *wl, u8 *addr)
{
	struct wl1271_acx_inconnection_sta *acx = NULL;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx set inconnaction sta %pM", addr);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	memcpy(acx->addr, addr, ETH_ALEN);

	ret = wl1271_cmd_configure(wl, ACX_UPDATE_INCONNECTION_STA_LIST,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx set inconnaction sta failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}