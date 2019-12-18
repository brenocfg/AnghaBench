#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int /*<<< orphan*/  channel_changed; int /*<<< orphan*/  rc; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  controller; } ;
struct TYPE_6__ {TYPE_1__ self; } ;
struct wusbhc {TYPE_3__ pal; int /*<<< orphan*/  uwb_rc; TYPE_2__ usb_hcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_pal_init (TYPE_3__*) ; 
 int uwb_pal_register (TYPE_3__*) ; 
 int /*<<< orphan*/  wusbhc_channel_changed ; 

int wusbhc_pal_register(struct wusbhc *wusbhc)
{
	uwb_pal_init(&wusbhc->pal);

	wusbhc->pal.name   = "wusbhc";
	wusbhc->pal.device = wusbhc->usb_hcd.self.controller;
	wusbhc->pal.rc     = wusbhc->uwb_rc;
	wusbhc->pal.channel_changed = wusbhc_channel_changed;

	return uwb_pal_register(&wusbhc->pal);
}