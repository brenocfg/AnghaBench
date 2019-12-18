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
typedef  size_t u16 ;
struct wl1271 {int dummy; } ;
struct acx_header {void* len; void* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CONFIGURE ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 
 int wlcore_cmd_send_failsafe (struct wl1271*,int /*<<< orphan*/ ,struct acx_header*,size_t,int /*<<< orphan*/ ,unsigned long) ; 

int wlcore_cmd_configure_failsafe(struct wl1271 *wl, u16 id, void *buf,
				  size_t len, unsigned long valid_rets)
{
	struct acx_header *acx = buf;
	int ret;

	wl1271_debug(DEBUG_CMD, "cmd configure (%d)", id);

	acx->id = cpu_to_le16(id);

	/* payload length, does not include any headers */
	acx->len = cpu_to_le16(len - sizeof(*acx));

	ret = wlcore_cmd_send_failsafe(wl, CMD_CONFIGURE, acx, len, 0,
				       valid_rets);
	if (ret < 0) {
		wl1271_warning("CONFIGURE command NOK");
		return ret;
	}

	return ret;
}