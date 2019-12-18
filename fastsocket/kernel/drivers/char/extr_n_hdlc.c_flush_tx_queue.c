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
struct tty_struct {int dummy; } ;
struct n_hdlc_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; } ;
struct n_hdlc {TYPE_1__ tx_buf_list; struct n_hdlc_buf* tbuf; int /*<<< orphan*/  tx_free_buf_list; } ;

/* Variables and functions */
 struct n_hdlc_buf* n_hdlc_buf_get (TYPE_1__*) ; 
 int /*<<< orphan*/  n_hdlc_buf_put (int /*<<< orphan*/ *,struct n_hdlc_buf*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct n_hdlc* tty2n_hdlc (struct tty_struct*) ; 

__attribute__((used)) static void flush_tx_queue(struct tty_struct *tty)
{
	struct n_hdlc *n_hdlc = tty2n_hdlc(tty);
	struct n_hdlc_buf *buf;
	unsigned long flags;

	while ((buf = n_hdlc_buf_get(&n_hdlc->tx_buf_list)))
		n_hdlc_buf_put(&n_hdlc->tx_free_buf_list, buf);
 	spin_lock_irqsave(&n_hdlc->tx_buf_list.spinlock, flags);
	if (n_hdlc->tbuf) {
		n_hdlc_buf_put(&n_hdlc->tx_free_buf_list, n_hdlc->tbuf);
		n_hdlc->tbuf = NULL;
	}
	spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock, flags);
}