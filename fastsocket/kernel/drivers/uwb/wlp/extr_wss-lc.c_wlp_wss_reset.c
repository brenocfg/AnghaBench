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
struct wlp_wss {int /*<<< orphan*/  state; scalar_t__ tag; int /*<<< orphan*/ * master_key; int /*<<< orphan*/  secure_status; int /*<<< orphan*/  bcast; int /*<<< orphan*/ * name; scalar_t__ hash; int /*<<< orphan*/  wssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLP_WSS_STATE_NONE ; 
 int /*<<< orphan*/  WLP_WSS_UNSECURE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void wlp_wss_reset(struct wlp_wss *wss)
{
	memset(&wss->wssid, 0, sizeof(wss->wssid));
	wss->hash = 0;
	memset(&wss->name[0], 0, sizeof(wss->name));
	memset(&wss->bcast, 0, sizeof(wss->bcast));
	wss->secure_status = WLP_WSS_UNSECURE;
	memset(&wss->master_key[0], 0, sizeof(wss->master_key));
	wss->tag = 0;
	wss->state = WLP_WSS_STATE_NONE;
}