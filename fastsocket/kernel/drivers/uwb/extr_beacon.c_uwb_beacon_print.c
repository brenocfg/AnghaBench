#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uwb_rc_evt_beacon {int /*<<< orphan*/  wBPSTOffset; int /*<<< orphan*/  bChannelNumber; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  DestAddr; int /*<<< orphan*/  SrcAddr; } ;
struct uwb_beacon_frame {int /*<<< orphan*/  Beacon_Slot_Number; TYPE_2__ hdr; int /*<<< orphan*/  Device_Identifier; } ;
typedef  int /*<<< orphan*/  macbuf ;
typedef  int /*<<< orphan*/  dstbuf ;
typedef  int /*<<< orphan*/  devbuf ;

/* Variables and functions */
 int UWB_ADDR_STRSIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uwb_dev_addr_print (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_mac_addr_print (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uwb_beacon_print(struct uwb_rc *rc, struct uwb_rc_evt_beacon *be,
			     struct uwb_beacon_frame *bf)
{
	char macbuf[UWB_ADDR_STRSIZE];
	char devbuf[UWB_ADDR_STRSIZE];
	char dstbuf[UWB_ADDR_STRSIZE];

	uwb_mac_addr_print(macbuf, sizeof(macbuf), &bf->Device_Identifier);
	uwb_dev_addr_print(devbuf, sizeof(devbuf), &bf->hdr.SrcAddr);
	uwb_dev_addr_print(dstbuf, sizeof(dstbuf), &bf->hdr.DestAddr);
	dev_info(&rc->uwb_dev.dev,
		 "BEACON from %s to %s (ch%u offset %u slot %u MAC %s)\n",
		 devbuf, dstbuf, be->bChannelNumber, be->wBPSTOffset,
		 bf->Beacon_Slot_Number, macbuf);
}