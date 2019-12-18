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
struct usb_function {int dummy; } ;
struct phonet_port {int /*<<< orphan*/  lock; } ;
struct f_phonet {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pn_reset (struct usb_function*) ; 
 struct f_phonet* func_to_pn (struct usb_function*) ; 
 struct phonet_port* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pn_disconnect(struct usb_function *f)
{
	struct f_phonet *fp = func_to_pn(f);
	struct phonet_port *port = netdev_priv(fp->dev);
	unsigned long flags;

	/* remain disabled until set_alt */
	spin_lock_irqsave(&port->lock, flags);
	__pn_reset(f);
	spin_unlock_irqrestore(&port->lock, flags);
}