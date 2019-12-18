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
struct wl3501_scan_req {int probe_delay; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  max_chan_time; int /*<<< orphan*/  min_chan_time; int /*<<< orphan*/  scan_type; int /*<<< orphan*/  sig_id; } ;
struct wl3501_card {scalar_t__ join_sta_bss; scalar_t__ bss_cnt; } ;
typedef  int /*<<< orphan*/  sig ;

/* Variables and functions */
 int /*<<< orphan*/  WL3501_SCAN_TYPE_ACTIVE ; 
 int /*<<< orphan*/  WL3501_SIG_SCAN_REQ ; 
 int wl3501_esbq_exec (struct wl3501_card*,struct wl3501_scan_req*,int) ; 
 int /*<<< orphan*/  wl3501_fw_bss_type (struct wl3501_card*) ; 

__attribute__((used)) static int wl3501_mgmt_scan(struct wl3501_card *this, u16 chan_time)
{
	struct wl3501_scan_req sig = {
		.sig_id		= WL3501_SIG_SCAN_REQ,
		.scan_type	= WL3501_SCAN_TYPE_ACTIVE,
		.probe_delay	= 0x10,
		.min_chan_time	= chan_time,
		.max_chan_time	= chan_time,
		.bss_type	= wl3501_fw_bss_type(this),
	};

	this->bss_cnt = this->join_sta_bss = 0;
	return wl3501_esbq_exec(this, &sig, sizeof(sig));
}