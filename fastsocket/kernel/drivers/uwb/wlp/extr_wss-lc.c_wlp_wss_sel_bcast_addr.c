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
struct wlp_wss {int dummy; } ;
struct uwb_mac_addr {int /*<<< orphan*/  data; } ;

/* Variables and functions */

__attribute__((used)) static
struct uwb_mac_addr wlp_wss_sel_bcast_addr(struct wlp_wss *wss)
{
	struct uwb_mac_addr bcast = {
		.data = { 0x01, 0x13, 0x88, 0x00, 0x01, 0x00 }
	};
	return bcast;
}