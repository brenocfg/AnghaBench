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
struct omap_mbox2_fifo {int /*<<< orphan*/  msg; } ;
struct omap_mbox2_priv {struct omap_mbox2_fifo tx_fifo; } ;
struct omap_mbox {scalar_t__ priv; } ;
typedef  int /*<<< orphan*/  mbox_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_mbox_fifo_write(struct omap_mbox *mbox, mbox_msg_t msg)
{
	struct omap_mbox2_fifo *fifo =
		&((struct omap_mbox2_priv *)mbox->priv)->tx_fifo;
	mbox_write_reg(msg, fifo->msg);
}