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
struct wl1271_static_data {int dummy; } ;
struct wl1271 {int static_data_priv_len; int /*<<< orphan*/  cmd_box_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1271_static_data*) ; 
 struct wl1271_static_data* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int wlcore_boot_parse_fw_ver (struct wl1271*,struct wl1271_static_data*) ; 
 int wlcore_handle_static_data (struct wl1271*,struct wl1271_static_data*) ; 
 int wlcore_read (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_static_data*,size_t,int) ; 
 int wlcore_validate_fw_ver (struct wl1271*) ; 

__attribute__((used)) static int wlcore_boot_static_data(struct wl1271 *wl)
{
	struct wl1271_static_data *static_data;
	size_t len = sizeof(*static_data) + wl->static_data_priv_len;
	int ret;

	static_data = kmalloc(len, GFP_KERNEL);
	if (!static_data) {
		ret = -ENOMEM;
		goto out;
	}

	ret = wlcore_read(wl, wl->cmd_box_addr, static_data, len, false);
	if (ret < 0)
		goto out_free;

	ret = wlcore_boot_parse_fw_ver(wl, static_data);
	if (ret < 0)
		goto out_free;

	ret = wlcore_validate_fw_ver(wl);
	if (ret < 0)
		goto out_free;

	ret = wlcore_handle_static_data(wl, static_data);
	if (ret < 0)
		goto out_free;

out_free:
	kfree(static_data);
out:
	return ret;
}