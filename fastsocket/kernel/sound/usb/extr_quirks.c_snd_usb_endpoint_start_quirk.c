#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_usb_endpoint {scalar_t__ type; int skip_packets; TYPE_3__* chip; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  idVendor; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 scalar_t__ SND_USB_ENDPOINT_TYPE_SYNC ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

void snd_usb_endpoint_start_quirk(struct snd_usb_endpoint *ep)
{
	/*
	 * "Playback Design" products send bogus feedback data at the start
	 * of the stream. Ignore them.
	 */
	if ((le16_to_cpu(ep->chip->dev->descriptor.idVendor) == 0x23ba) &&
	    ep->type == SND_USB_ENDPOINT_TYPE_SYNC)
		ep->skip_packets = 4;
}