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
struct isi_port {int dummy; } ;
struct isi_board {int status; int port_count; int /*<<< orphan*/  card_lock; struct isi_port* ports; } ;

/* Variables and functions */
 int BOARD_ACTIVE ; 
 int /*<<< orphan*/  drop_dtr_rts (struct isi_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void isicom_setup_board(struct isi_board *bp)
{
	int channel;
	struct isi_port *port;
	unsigned long flags;

	spin_lock_irqsave(&bp->card_lock, flags);
	if (bp->status & BOARD_ACTIVE) {
		spin_unlock_irqrestore(&bp->card_lock, flags);
		return;
	}
	port = bp->ports;
	bp->status |= BOARD_ACTIVE;
	for (channel = 0; channel < bp->port_count; channel++, port++)
		drop_dtr_rts(port);
	spin_unlock_irqrestore(&bp->card_lock, flags);
}