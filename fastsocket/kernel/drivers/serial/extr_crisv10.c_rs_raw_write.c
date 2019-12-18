#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* chars_in_buffer ) (struct tty_struct*) ;} ;
struct tty_struct {int /*<<< orphan*/  hw_stopped; int /*<<< orphan*/  stopped; TYPE_1__ ldisc; scalar_t__ driver_data; } ;
struct TYPE_4__ {int head; int tail; scalar_t__ buf; } ;
struct e100_serial {scalar_t__ line; int /*<<< orphan*/  tr_running; TYPE_2__ xmit; int /*<<< orphan*/ * ioport; } ;

/* Variables and functions */
 int CIRC_SPACE_TO_END (int,int,int) ; 
 int /*<<< orphan*/  DEBUG_LOG (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 size_t REG_STATUS ; 
 scalar_t__ SERIAL_DEBUG_LINE ; 
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  SIMCOUT (unsigned char const*,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_transmit (struct e100_serial*) ; 
 int stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  tmp_buf ; 

__attribute__((used)) static int rs_raw_write(struct tty_struct *tty,
			const unsigned char *buf, int count)
{
	int	c, ret = 0;
	struct e100_serial *info = (struct e100_serial *)tty->driver_data;
	unsigned long flags;

	/* first some sanity checks */

	if (!tty || !info->xmit.buf || !tmp_buf)
		return 0;

#ifdef SERIAL_DEBUG_DATA
	if (info->line == SERIAL_DEBUG_LINE)
		printk("rs_raw_write (%d), status %d\n",
		       count, info->ioport[REG_STATUS]);
#endif

#ifdef CONFIG_SVINTO_SIM
	/* Really simple.  The output is here and now. */
	SIMCOUT(buf, count);
	return count;
#endif
	local_save_flags(flags);
	DFLOW(DEBUG_LOG(info->line, "write count %i ", count));
	DFLOW(DEBUG_LOG(info->line, "ldisc %i\n", tty->ldisc.chars_in_buffer(tty)));


	/* The local_irq_disable/restore_flags pairs below are needed
	 * because the DMA interrupt handler moves the info->xmit values.
	 * the memcpy needs to be in the critical region unfortunately,
	 * because we need to read xmit values, memcpy, write xmit values
	 * in one atomic operation... this could perhaps be avoided by
	 * more clever design.
	 */
	local_irq_disable();
		while (count) {
			c = CIRC_SPACE_TO_END(info->xmit.head,
					      info->xmit.tail,
					      SERIAL_XMIT_SIZE);

			if (count < c)
				c = count;
			if (c <= 0)
				break;

			memcpy(info->xmit.buf + info->xmit.head, buf, c);
			info->xmit.head = (info->xmit.head + c) &
				(SERIAL_XMIT_SIZE-1);
			buf += c;
			count -= c;
			ret += c;
		}
	local_irq_restore(flags);

	/* enable transmitter if not running, unless the tty is stopped
	 * this does not need IRQ protection since if tr_running == 0
	 * the IRQ's are not running anyway for this port.
	 */
	DFLOW(DEBUG_LOG(info->line, "write ret %i\n", ret));

	if (info->xmit.head != info->xmit.tail &&
	    !tty->stopped &&
	    !tty->hw_stopped &&
	    !info->tr_running) {
		start_transmit(info);
	}

	return ret;
}