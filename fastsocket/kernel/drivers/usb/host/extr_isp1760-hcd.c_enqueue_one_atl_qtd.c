#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct usb_hcd {size_t regs; } ;
struct urb {int dummy; } ;
struct ptd {int dummy; } ;
struct isp1760_qtd {int status; int /*<<< orphan*/  data_buffer; } ;
struct isp1760_qh {int dummy; } ;
struct isp1760_hcd {TYPE_1__* atl_ints; } ;
typedef  int /*<<< orphan*/  ptd ;
struct TYPE_2__ {size_t payload; int /*<<< orphan*/  data_buffer; struct isp1760_qtd* qtd; struct isp1760_qh* qh; struct urb* urb; } ;

/* Variables and functions */
 int URB_ENQUEUED ; 
 int URB_TYPE_ATL ; 
 int /*<<< orphan*/  enqueue_one_qtd (struct isp1760_qtd*,struct isp1760_hcd*,size_t) ; 
 struct usb_hcd* priv_to_hcd (struct isp1760_hcd*) ; 
 int /*<<< orphan*/  priv_write_copy (struct isp1760_hcd*,size_t*,size_t,int) ; 
 int /*<<< orphan*/  transform_into_atl (struct isp1760_hcd*,struct isp1760_qh*,struct isp1760_qtd*,struct urb*,size_t,struct ptd*) ; 

__attribute__((used)) static void enqueue_one_atl_qtd(u32 atl_regs, u32 payload,
		struct isp1760_hcd *priv, struct isp1760_qh *qh,
		struct urb *urb, u32 slot, struct isp1760_qtd *qtd)
{
	struct ptd ptd;
	struct usb_hcd *hcd = priv_to_hcd(priv);

	transform_into_atl(priv, qh, qtd, urb, payload, &ptd);
	priv_write_copy(priv, (u32 *)&ptd, hcd->regs + atl_regs, sizeof(ptd));
	enqueue_one_qtd(qtd, priv, payload);

	priv->atl_ints[slot].urb = urb;
	priv->atl_ints[slot].qh = qh;
	priv->atl_ints[slot].qtd = qtd;
	priv->atl_ints[slot].data_buffer = qtd->data_buffer;
	priv->atl_ints[slot].payload = payload;
	qtd->status |= URB_ENQUEUED | URB_TYPE_ATL;
	qtd->status |= slot << 16;
}