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
struct omap_mbox2_fifo {int /*<<< orphan*/  msg_stat; } ;
struct omap_mbox2_priv {struct omap_mbox2_fifo rx_fifo; } ;
struct omap_mbox {scalar_t__ priv; } ;

/* Variables and functions */
 scalar_t__ mbox_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_mbox_fifo_empty(struct omap_mbox *mbox)
{
	struct omap_mbox2_fifo *fifo =
		&((struct omap_mbox2_priv *)mbox->priv)->rx_fifo;
	return (mbox_read_reg(fifo->msg_stat) == 0);
}