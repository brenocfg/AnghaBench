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
struct urb {int dummy; } ;
struct snd_usb_endpoint {scalar_t__ skip_packets; int /*<<< orphan*/  data_subs; int /*<<< orphan*/  (* retire_data_urb ) (int /*<<< orphan*/ ,struct urb*) ;scalar_t__ sync_slave; } ;
struct snd_urb_ctx {struct urb* urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_usb_handle_sync_urb (scalar_t__,struct snd_usb_endpoint*,struct urb*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct urb*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void retire_inbound_urb(struct snd_usb_endpoint *ep,
			       struct snd_urb_ctx *urb_ctx)
{
	struct urb *urb = urb_ctx->urb;

	if (unlikely(ep->skip_packets > 0)) {
		ep->skip_packets--;
		return;
	}

	if (ep->sync_slave)
		snd_usb_handle_sync_urb(ep->sync_slave, ep, urb);

	if (ep->retire_data_urb)
		ep->retire_data_urb(ep->data_subs, urb);
}