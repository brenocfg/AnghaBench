#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct r_port* driver_data; } ;
struct TYPE_3__ {unsigned int* TxControl; } ;
struct r_port {TYPE_1__ channel; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int CD_ACT ; 
 unsigned int CTS_ACT ; 
 unsigned int DSR_ACT ; 
 unsigned int SET_DTR ; 
 unsigned int SET_RTS ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RNG ; 
 unsigned int TIOCM_RTS ; 
 scalar_t__ sGetChanRI (TYPE_1__*) ; 
 unsigned int sGetChanStatusLo (TYPE_1__*) ; 

__attribute__((used)) static int rp_tiocmget(struct tty_struct *tty, struct file *file)
{
	struct r_port *info = tty->driver_data;
	unsigned int control, result, ChanStatus;

	ChanStatus = sGetChanStatusLo(&info->channel);
	control = info->channel.TxControl[3];
	result = ((control & SET_RTS) ? TIOCM_RTS : 0) | 
		((control & SET_DTR) ?  TIOCM_DTR : 0) |
		((ChanStatus & CD_ACT) ? TIOCM_CAR : 0) |
		(sGetChanRI(&info->channel) ? TIOCM_RNG : 0) |
		((ChanStatus & DSR_ACT) ? TIOCM_DSR : 0) |
		((ChanStatus & CTS_ACT) ? TIOCM_CTS : 0);

	return result;
}