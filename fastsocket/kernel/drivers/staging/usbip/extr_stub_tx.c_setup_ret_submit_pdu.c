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
struct usbip_header {int /*<<< orphan*/  base; } ;
struct urb {scalar_t__ context; } ;
struct stub_priv {int /*<<< orphan*/  seqnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBIP_RET_SUBMIT ; 
 int /*<<< orphan*/  setup_base_pdu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_pack_pdu (struct usbip_header*,struct urb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_ret_submit_pdu(struct usbip_header *rpdu, struct urb *urb)
{
	struct stub_priv *priv = (struct stub_priv *) urb->context;

	setup_base_pdu(&rpdu->base, USBIP_RET_SUBMIT, priv->seqnum);

	usbip_pack_pdu(rpdu, urb, USBIP_RET_SUBMIT, 1);
}