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
struct kiocb_priv {scalar_t__ req; struct ep_data* epdata; } ;
struct kiocb {struct kiocb_priv* private; } ;
struct io_event {int dummy; } ;
struct ep_data {scalar_t__ ep; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  aio_put_req (struct kiocb*) ; 
 int /*<<< orphan*/  kiocbSetCancelled (struct kiocb*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int usb_ep_dequeue (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ep_aio_cancel(struct kiocb *iocb, struct io_event *e)
{
	struct kiocb_priv	*priv = iocb->private;
	struct ep_data		*epdata;
	int			value;

	local_irq_disable();
	epdata = priv->epdata;
	// spin_lock(&epdata->dev->lock);
	kiocbSetCancelled(iocb);
	if (likely(epdata && epdata->ep && priv->req))
		value = usb_ep_dequeue (epdata->ep, priv->req);
	else
		value = -EINVAL;
	// spin_unlock(&epdata->dev->lock);
	local_irq_enable();

	aio_put_req(iocb);
	return value;
}