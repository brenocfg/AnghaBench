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
struct wusbhc {int dummy; } ;
struct wusb_dn_hdr {int dummy; } ;
struct whc {struct dn_buf_entry* dn_buf; struct wusbhc wusbhc; } ;
struct dn_buf_entry {int status; int /*<<< orphan*/  msg_size; scalar_t__ dn_data; int /*<<< orphan*/  src_addr; } ;

/* Variables and functions */
 int WHC_DN_STATUS_VALID ; 
 int WHC_N_DN_ENTRIES ; 
 int /*<<< orphan*/  wusbhc_handle_dn (struct wusbhc*,int /*<<< orphan*/ ,struct wusb_dn_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_dn_buf(struct whc *whc)
{
	struct wusbhc *wusbhc = &whc->wusbhc;
	struct dn_buf_entry *dn;
	int processed = 0;

	for (dn = whc->dn_buf; dn < whc->dn_buf + WHC_N_DN_ENTRIES; dn++) {
		if (dn->status & WHC_DN_STATUS_VALID) {
			wusbhc_handle_dn(wusbhc, dn->src_addr,
					 (struct wusb_dn_hdr *)dn->dn_data,
					 dn->msg_size);
			dn->status &= ~WHC_DN_STATUS_VALID;
			processed++;
		}
	}
	return processed;
}