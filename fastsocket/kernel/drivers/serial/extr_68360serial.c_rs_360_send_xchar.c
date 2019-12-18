#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_4__ {TYPE_2__* tx_cur; TYPE_2__* tx_bd_base; } ;
typedef  TYPE_1__ ser_info_t ;
struct TYPE_5__ {int status; int length; scalar_t__ buf; } ;
typedef  TYPE_2__ QUICC_BD ;

/* Variables and functions */
 int BD_SC_READY ; 
 int BD_SC_WRAP ; 
 scalar_t__ serial_paranoia_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void rs_360_send_xchar(struct tty_struct *tty, char ch)
{
	volatile QUICC_BD	*bdp;

	ser_info_t *info = (ser_info_t *)tty->driver_data;

	if (serial_paranoia_check(info, tty->name, "rs_send_char"))
		return;

	bdp = info->tx_cur;
	while (bdp->status & BD_SC_READY);

	/* *((char *)__va(bdp->buf)) = ch; */
	*((char *)bdp->buf) = ch;
	bdp->length = 1;
	bdp->status |= BD_SC_READY;

	/* Get next BD.
	*/
	if (bdp->status & BD_SC_WRAP)
		bdp = info->tx_bd_base;
	else
		bdp++;

	info->tx_cur = (QUICC_BD *)bdp;
}