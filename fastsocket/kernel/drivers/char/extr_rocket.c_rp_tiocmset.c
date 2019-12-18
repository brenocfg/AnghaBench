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
struct tty_struct {struct r_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * TxControl; int /*<<< orphan*/  IndexAddr; } ;
struct r_port {TYPE_1__ channel; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_DTR ; 
 int /*<<< orphan*/  SET_RTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  out32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rp_tiocmset(struct tty_struct *tty, struct file *file,
		    unsigned int set, unsigned int clear)
{
	struct r_port *info = tty->driver_data;

	if (set & TIOCM_RTS)
		info->channel.TxControl[3] |= SET_RTS;
	if (set & TIOCM_DTR)
		info->channel.TxControl[3] |= SET_DTR;
	if (clear & TIOCM_RTS)
		info->channel.TxControl[3] &= ~SET_RTS;
	if (clear & TIOCM_DTR)
		info->channel.TxControl[3] &= ~SET_DTR;

	out32(info->channel.IndexAddr, info->channel.TxControl);
	return 0;
}