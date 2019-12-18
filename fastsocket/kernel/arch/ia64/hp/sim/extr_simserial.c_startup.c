#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct serial_state {size_t irq; int /*<<< orphan*/  type; int /*<<< orphan*/  port; } ;
struct TYPE_4__ {unsigned char* buf; scalar_t__ tail; scalar_t__ head; } ;
struct async_struct {int flags; TYPE_2__* tty; TYPE_1__ xmit; struct async_struct* prev_port; struct async_struct* next_port; int /*<<< orphan*/  line; struct serial_state* state; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {int alt_speed; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int ASYNC_SPD_HI ; 
 int ASYNC_SPD_MASK ; 
 int ASYNC_SPD_SHI ; 
 int ASYNC_SPD_VHI ; 
 int ASYNC_SPD_WARP ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  IRQ_T (struct async_struct*) ; 
 struct async_struct** IRQ_ports ; 
 size_t RS_TIMER ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,size_t) ; 
 int request_irq (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rs_interrupt_single ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int timer_active ; 
 TYPE_3__* timer_table ; 

__attribute__((used)) static int
startup(struct async_struct *info)
{
	unsigned long flags;
	int	retval=0;
	irq_handler_t handler;
	struct serial_state *state= info->state;
	unsigned long page;

	page = get_zeroed_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	local_irq_save(flags);

	if (info->flags & ASYNC_INITIALIZED) {
		free_page(page);
		goto errout;
	}

	if (!state->port || !state->type) {
		if (info->tty) set_bit(TTY_IO_ERROR, &info->tty->flags);
		free_page(page);
		goto errout;
	}
	if (info->xmit.buf)
		free_page(page);
	else
		info->xmit.buf = (unsigned char *) page;

#ifdef SIMSERIAL_DEBUG
	printk("startup: ttys%d (irq %d)...", info->line, state->irq);
#endif

	/*
	 * Allocate the IRQ if necessary
	 */
	if (state->irq && (!IRQ_ports[state->irq] ||
			  !IRQ_ports[state->irq]->next_port)) {
		if (IRQ_ports[state->irq]) {
			retval = -EBUSY;
			goto errout;
		} else
			handler = rs_interrupt_single;

		retval = request_irq(state->irq, handler, IRQ_T(info), "simserial", NULL);
		if (retval) {
			if (capable(CAP_SYS_ADMIN)) {
				if (info->tty)
					set_bit(TTY_IO_ERROR,
						&info->tty->flags);
				retval = 0;
			}
			goto errout;
		}
	}

	/*
	 * Insert serial port into IRQ chain.
	 */
	info->prev_port = NULL;
	info->next_port = IRQ_ports[state->irq];
	if (info->next_port)
		info->next_port->prev_port = info;
	IRQ_ports[state->irq] = info;

	if (info->tty) clear_bit(TTY_IO_ERROR, &info->tty->flags);

	info->xmit.head = info->xmit.tail = 0;

#if 0
	/*
	 * Set up serial timers...
	 */
	timer_table[RS_TIMER].expires = jiffies + 2*HZ/100;
	timer_active |= 1 << RS_TIMER;
#endif

	/*
	 * Set up the tty->alt_speed kludge
	 */
	if (info->tty) {
		if ((info->flags & ASYNC_SPD_MASK) == ASYNC_SPD_HI)
			info->tty->alt_speed = 57600;
		if ((info->flags & ASYNC_SPD_MASK) == ASYNC_SPD_VHI)
			info->tty->alt_speed = 115200;
		if ((info->flags & ASYNC_SPD_MASK) == ASYNC_SPD_SHI)
			info->tty->alt_speed = 230400;
		if ((info->flags & ASYNC_SPD_MASK) == ASYNC_SPD_WARP)
			info->tty->alt_speed = 460800;
	}

	info->flags |= ASYNC_INITIALIZED;
	local_irq_restore(flags);
	return 0;

errout:
	local_irq_restore(flags);
	return retval;
}