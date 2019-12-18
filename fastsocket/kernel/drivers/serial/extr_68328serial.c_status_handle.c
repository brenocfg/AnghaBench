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
struct TYPE_6__ {TYPE_2__* tty; } ;
struct m68k_serial {int* curregs; int* pendregs; scalar_t__ break_abort; int /*<<< orphan*/  m68k_channel; TYPE_3__ port; } ;
struct TYPE_5__ {TYPE_1__* termios; } ;
struct TYPE_4__ {int c_cflag; } ;

/* Variables and functions */
 int AUTO_ENAB ; 
 int CRTSCTS ; 
 unsigned short DCD ; 
 unsigned short URX_BREAK ; 
 int /*<<< orphan*/  batten_down_hatches () ; 
 int /*<<< orphan*/  write_zsreg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void status_handle(struct m68k_serial *info, unsigned short status)
{
#if 0
	if(status & DCD) {
		if((info->port.tty->termios->c_cflag & CRTSCTS) &&
		   ((info->curregs[3] & AUTO_ENAB)==0)) {
			info->curregs[3] |= AUTO_ENAB;
			info->pendregs[3] |= AUTO_ENAB;
			write_zsreg(info->m68k_channel, 3, info->curregs[3]);
		}
	} else {
		if((info->curregs[3] & AUTO_ENAB)) {
			info->curregs[3] &= ~AUTO_ENAB;
			info->pendregs[3] &= ~AUTO_ENAB;
			write_zsreg(info->m68k_channel, 3, info->curregs[3]);
		}
	}
#endif
	/* If this is console input and this is a
	 * 'break asserted' status change interrupt
	 * see if we can drop into the debugger
	 */
	if((status & URX_BREAK) && info->break_abort)
		batten_down_hatches();
	return;
}