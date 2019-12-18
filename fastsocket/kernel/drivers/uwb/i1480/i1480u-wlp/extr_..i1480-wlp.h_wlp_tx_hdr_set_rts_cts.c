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
struct wlp_tx_hdr {int mac_params; } ;

/* Variables and functions */

__attribute__((used)) static inline void wlp_tx_hdr_set_rts_cts(struct wlp_tx_hdr *hdr, int rts_cts)
{
	hdr->mac_params = (hdr->mac_params & ~0x80) | (rts_cts << 7);
}