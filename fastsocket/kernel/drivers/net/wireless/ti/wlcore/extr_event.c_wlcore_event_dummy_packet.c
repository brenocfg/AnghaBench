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
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_tx_dummy_packet (struct wl1271*) ; 

void wlcore_event_dummy_packet(struct wl1271 *wl)
{
	wl1271_debug(DEBUG_EVENT, "DUMMY_PACKET_ID_EVENT_ID");
	wl1271_tx_dummy_packet(wl);
}