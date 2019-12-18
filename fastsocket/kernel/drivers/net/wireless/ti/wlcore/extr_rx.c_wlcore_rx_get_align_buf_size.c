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
typedef  int /*<<< orphan*/  u32 ;
struct wl1271 {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WL12XX_BUS_BLOCK_SIZE ; 
 int WLCORE_QUIRK_RX_BLOCKSIZE_ALIGN ; 

__attribute__((used)) static u32 wlcore_rx_get_align_buf_size(struct wl1271 *wl, u32 pkt_len)
{
	if (wl->quirks & WLCORE_QUIRK_RX_BLOCKSIZE_ALIGN)
		return ALIGN(pkt_len, WL12XX_BUS_BLOCK_SIZE);

	return pkt_len;
}