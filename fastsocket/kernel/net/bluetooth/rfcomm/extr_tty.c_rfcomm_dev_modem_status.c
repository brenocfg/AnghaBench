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
typedef  int u8 ;
struct rfcomm_dlc {struct rfcomm_dev* owner; } ;
struct rfcomm_dev {int modem_status; scalar_t__ tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,struct rfcomm_dev*,int) ; 
 int /*<<< orphan*/  C_CLOCAL (scalar_t__) ; 
 int RFCOMM_V24_DV ; 
 int RFCOMM_V24_IC ; 
 int RFCOMM_V24_RTC ; 
 int RFCOMM_V24_RTR ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RI ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  tty_hangup (scalar_t__) ; 

__attribute__((used)) static void rfcomm_dev_modem_status(struct rfcomm_dlc *dlc, u8 v24_sig)
{
	struct rfcomm_dev *dev = dlc->owner;
	if (!dev)
		return;

	BT_DBG("dlc %p dev %p v24_sig 0x%02x", dlc, dev, v24_sig);

	if ((dev->modem_status & TIOCM_CD) && !(v24_sig & RFCOMM_V24_DV)) {
		if (dev->tty && !C_CLOCAL(dev->tty))
			tty_hangup(dev->tty);
	}

	dev->modem_status =
		((v24_sig & RFCOMM_V24_RTC) ? (TIOCM_DSR | TIOCM_DTR) : 0) |
		((v24_sig & RFCOMM_V24_RTR) ? (TIOCM_RTS | TIOCM_CTS) : 0) |
		((v24_sig & RFCOMM_V24_IC)  ? TIOCM_RI : 0) |
		((v24_sig & RFCOMM_V24_DV)  ? TIOCM_CD : 0);
}