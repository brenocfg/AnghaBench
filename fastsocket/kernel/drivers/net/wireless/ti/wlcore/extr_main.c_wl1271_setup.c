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
struct wl_fw_status_2 {int dummy; } ;
struct wl1271 {int fw_status_priv_len; void* fw_status_1; void* tx_res_if; int /*<<< orphan*/  num_rx_desc; struct wl_fw_status_2* fw_status_2; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WLCORE_FW_STATUS_1_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1271_setup(struct wl1271 *wl)
{
	wl->fw_status_1 = kmalloc(WLCORE_FW_STATUS_1_LEN(wl->num_rx_desc) +
				  sizeof(*wl->fw_status_2) +
				  wl->fw_status_priv_len, GFP_KERNEL);
	if (!wl->fw_status_1)
		return -ENOMEM;

	wl->fw_status_2 = (struct wl_fw_status_2 *)
				(((u8 *) wl->fw_status_1) +
				WLCORE_FW_STATUS_1_LEN(wl->num_rx_desc));

	wl->tx_res_if = kmalloc(sizeof(*wl->tx_res_if), GFP_KERNEL);
	if (!wl->tx_res_if) {
		kfree(wl->fw_status_1);
		return -ENOMEM;
	}

	return 0;
}