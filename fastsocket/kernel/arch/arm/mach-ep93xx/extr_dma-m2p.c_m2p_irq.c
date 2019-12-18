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
typedef  int u32 ;
struct m2p_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/ * buffer_next; int /*<<< orphan*/ * buffer_xfer; scalar_t__ base; struct ep93xx_dma_m2p_client* client; } ;
struct ep93xx_dma_m2p_client {int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* buffer_started ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* buffer_finished ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ M2P_CONTROL ; 
 int M2P_CONTROL_NFB_IRQ_EN ; 
 int M2P_CONTROL_STALL_IRQ_EN ; 
 scalar_t__ M2P_INTERRUPT ; 
 int M2P_INTERRUPT_ERROR ; 
 int M2P_INTERRUPT_NFB ; 
 int M2P_INTERRUPT_STALL ; 
#define  STATE_IDLE 131 
#define  STATE_NEXT 130 
#define  STATE_ON 129 
#define  STATE_STALL 128 
 int /*<<< orphan*/  choose_buffer_next (struct m2p_channel*) ; 
 int /*<<< orphan*/  choose_buffer_xfer (struct m2p_channel*) ; 
 int m2p_channel_state (struct m2p_channel*) ; 
 int /*<<< orphan*/  m2p_set_control (struct m2p_channel*,int) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t m2p_irq(int irq, void *dev_id)
{
	struct m2p_channel *ch = dev_id;
	struct ep93xx_dma_m2p_client *cl;
	u32 irq_status, v;
	int error = 0;

	cl = ch->client;

	spin_lock(&ch->lock);
	irq_status = readl(ch->base + M2P_INTERRUPT);

	if (irq_status & M2P_INTERRUPT_ERROR) {
		writel(M2P_INTERRUPT_ERROR, ch->base + M2P_INTERRUPT);
		error = 1;
	}

	if ((irq_status & (M2P_INTERRUPT_STALL | M2P_INTERRUPT_NFB)) == 0) {
		spin_unlock(&ch->lock);
		return IRQ_NONE;
	}

	switch (m2p_channel_state(ch)) {
	case STATE_IDLE:
		pr_crit("m2p_irq: dma interrupt without a dma buffer\n");
		BUG();
		break;

	case STATE_STALL:
		cl->buffer_finished(cl->cookie, ch->buffer_xfer, 0, error);
		if (ch->buffer_next != NULL) {
			cl->buffer_finished(cl->cookie, ch->buffer_next,
					    0, error);
		}
		choose_buffer_xfer(ch);
		choose_buffer_next(ch);
		if (ch->buffer_xfer != NULL)
			cl->buffer_started(cl->cookie, ch->buffer_xfer);
		break;

	case STATE_ON:
		cl->buffer_finished(cl->cookie, ch->buffer_xfer, 0, error);
		ch->buffer_xfer = ch->buffer_next;
		choose_buffer_next(ch);
		cl->buffer_started(cl->cookie, ch->buffer_xfer);
		break;

	case STATE_NEXT:
		pr_crit("m2p_irq: dma interrupt while next\n");
		BUG();
		break;
	}

	v = readl(ch->base + M2P_CONTROL) & ~(M2P_CONTROL_STALL_IRQ_EN |
					      M2P_CONTROL_NFB_IRQ_EN);
	if (ch->buffer_xfer != NULL)
		v |= M2P_CONTROL_STALL_IRQ_EN;
	if (ch->buffer_next != NULL)
		v |= M2P_CONTROL_NFB_IRQ_EN;
	m2p_set_control(ch, v);

	spin_unlock(&ch->lock);
	return IRQ_HANDLED;
}