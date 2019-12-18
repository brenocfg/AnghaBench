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
struct TYPE_3__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  overrun; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; } ;
struct e100_serial {unsigned char* ioport; size_t line; unsigned long last_rx_active_usec; unsigned long last_rx_active; char break_detected_cnt; scalar_t__ errorcode; int char_time_usec; int /*<<< orphan*/ * icmdadr; TYPE_1__ icount; int /*<<< orphan*/  uses_dma_in; } ;
struct TYPE_4__ {int /*<<< orphan*/  ser_ints_ok_cnt; int /*<<< orphan*/  early_errors_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (size_t,char*,unsigned char) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DINTR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DINTR2 (int /*<<< orphan*/ ) ; 
 scalar_t__ ERRCODE_INSERT_BREAK ; 
 scalar_t__ ERRCODE_SET_BREAK ; 
 void* GET_JIFFIES_USEC () ; 
 int HZ ; 
 unsigned char IO_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCSTAT (int /*<<< orphan*/ ) ; 
 size_t REG_DATA ; 
 size_t REG_STATUS ; 
 int /*<<< orphan*/  R_DMA_CH6_CMD ; 
 int /*<<< orphan*/  R_SERIAL0_STATUS ; 
 unsigned char SER_ERROR_MASK ; 
 unsigned char SER_FRAMING_ERR_MASK ; 
 unsigned char SER_OVERRUN_MASK ; 
 unsigned char SER_PAR_ERR_MASK ; 
 unsigned char SER_RXD_MASK ; 
 int /*<<< orphan*/  START_FLUSH_FAST_TIMER (struct e100_serial*,char*) ; 
 int /*<<< orphan*/  TTY_BREAK ; 
 int /*<<< orphan*/  TTY_FRAME ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 int /*<<< orphan*/  TTY_PARITY ; 
 int /*<<< orphan*/  add_char_and_flag (struct e100_serial*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd ; 
 int /*<<< orphan*/  e100_disable_serial_data_irq (struct e100_serial*) ; 
 struct e100_serial* handle_ser_rx_interrupt_no_dma (struct e100_serial*) ; 
 int /*<<< orphan*/  i ; 
 void* jiffies ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  restart ; 
 TYPE_2__* ser_stat ; 
 int /*<<< orphan*/  xoff_detect ; 

__attribute__((used)) static struct e100_serial* handle_ser_rx_interrupt(struct e100_serial *info)
{
	unsigned char rstat;

#ifdef SERIAL_DEBUG_INTR
	printk("Interrupt from serport %d\n", i);
#endif
/*	DEBUG_LOG(info->line, "ser_interrupt stat %03X\n", rstat | (i << 8)); */
	if (!info->uses_dma_in) {
		return handle_ser_rx_interrupt_no_dma(info);
	}
	/* DMA is used */
	rstat = info->ioport[REG_STATUS];
	if (rstat & IO_MASK(R_SERIAL0_STATUS, xoff_detect) ) {
		DFLOW(DEBUG_LOG(info->line, "XOFF detect\n", 0));
	}

	if (rstat & SER_ERROR_MASK) {
		unsigned char data;

		info->last_rx_active_usec = GET_JIFFIES_USEC();
		info->last_rx_active = jiffies;
		/* If we got an error, we must reset it by reading the
		 * data_in field
		 */
		data = info->ioport[REG_DATA];
		DINTR1(DEBUG_LOG(info->line, "ser_rx!  %c\n", data));
		DINTR1(DEBUG_LOG(info->line, "ser_rx err stat %02X\n", rstat));
		if (!data && (rstat & SER_FRAMING_ERR_MASK)) {
			/* Most likely a break, but we get interrupts over and
			 * over again.
			 */

			if (!info->break_detected_cnt) {
				DEBUG_LOG(info->line, "#BRK start\n", 0);
			}
			if (rstat & SER_RXD_MASK) {
				/* The RX pin is high now, so the break
				 * must be over, but....
				 * we can't really know if we will get another
				 * last byte ending the break or not.
				 * And we don't know if the byte (if any) will
				 * have an error or look valid.
				 */
				DEBUG_LOG(info->line, "# BL BRK\n", 0);
				info->errorcode = ERRCODE_INSERT_BREAK;
			}
			info->break_detected_cnt++;
		} else {
			/* The error does not look like a break, but could be
			 * the end of one
			 */
			if (info->break_detected_cnt) {
				DEBUG_LOG(info->line, "EBRK %i\n", info->break_detected_cnt);
				info->errorcode = ERRCODE_INSERT_BREAK;
			} else {
				if (info->errorcode == ERRCODE_INSERT_BREAK) {
					info->icount.brk++;
					add_char_and_flag(info, '\0', TTY_BREAK);
				}

				if (rstat & SER_PAR_ERR_MASK) {
					info->icount.parity++;
					add_char_and_flag(info, data, TTY_PARITY);
				} else if (rstat & SER_OVERRUN_MASK) {
					info->icount.overrun++;
					add_char_and_flag(info, data, TTY_OVERRUN);
				} else if (rstat & SER_FRAMING_ERR_MASK) {
					info->icount.frame++;
					add_char_and_flag(info, data, TTY_FRAME);
				}

				info->errorcode = 0;
			}
			info->break_detected_cnt = 0;
			DEBUG_LOG(info->line, "#iERR s d %04X\n",
			          ((rstat & SER_ERROR_MASK) << 8) | data);
		}
		PROCSTAT(ser_stat[info->line].early_errors_cnt++);
	} else { /* It was a valid byte, now let the DMA do the rest */
		unsigned long curr_time_u = GET_JIFFIES_USEC();
		unsigned long curr_time = jiffies;

		if (info->break_detected_cnt) {
			/* Detect if this character is a new valid char or the
			 * last char in a break sequence: If LSBits are 0 and
			 * MSBits are high AND the time is close to the
			 * previous interrupt we should discard it.
			 */
			long elapsed_usec =
			  (curr_time - info->last_rx_active) * (1000000/HZ) +
			  curr_time_u - info->last_rx_active_usec;
			if (elapsed_usec < 2*info->char_time_usec) {
				DEBUG_LOG(info->line, "FBRK %i\n", info->line);
				/* Report as BREAK (error) and let
				 * receive_chars_dma() handle it
				 */
				info->errorcode = ERRCODE_SET_BREAK;
			} else {
				DEBUG_LOG(info->line, "Not end of BRK (V)%i\n", info->line);
			}
			DEBUG_LOG(info->line, "num brk %i\n", info->break_detected_cnt);
		}

#ifdef SERIAL_DEBUG_INTR
		printk("** OK, disabling ser_interrupts\n");
#endif
		e100_disable_serial_data_irq(info);
		DINTR2(DEBUG_LOG(info->line, "ser_rx OK %d\n", info->line));
		info->break_detected_cnt = 0;

		PROCSTAT(ser_stat[info->line].ser_ints_ok_cnt++);
	}
	/* Restarting the DMA never hurts */
	*info->icmdadr = IO_STATE(R_DMA_CH6_CMD, cmd, restart);
	START_FLUSH_FAST_TIMER(info, "ser_int");
	return info;
}