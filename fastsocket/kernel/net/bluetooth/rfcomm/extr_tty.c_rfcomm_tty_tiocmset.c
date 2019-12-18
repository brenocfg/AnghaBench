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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {scalar_t__ driver_data; } ;
struct rfcomm_dlc {int dummy; } ;
struct rfcomm_dev {struct rfcomm_dlc* dlc; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*,struct rfcomm_dev*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  RFCOMM_V24_DV ; 
 int /*<<< orphan*/  RFCOMM_V24_IC ; 
 int /*<<< orphan*/  RFCOMM_V24_RTC ; 
 int /*<<< orphan*/  RFCOMM_V24_RTR ; 
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RI ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  rfcomm_dlc_get_modem_status (struct rfcomm_dlc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dlc_set_modem_status (struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfcomm_tty_tiocmset(struct tty_struct *tty, struct file *filp, unsigned int set, unsigned int clear)
{
	struct rfcomm_dev *dev = (struct rfcomm_dev *) tty->driver_data;
	struct rfcomm_dlc *dlc = dev->dlc;
	u8 v24_sig;

	BT_DBG("tty %p dev %p set 0x%02x clear 0x%02x", tty, dev, set, clear);

	rfcomm_dlc_get_modem_status(dlc, &v24_sig);

	if (set & TIOCM_DSR || set & TIOCM_DTR)
		v24_sig |= RFCOMM_V24_RTC;
	if (set & TIOCM_RTS || set & TIOCM_CTS)
		v24_sig |= RFCOMM_V24_RTR;
	if (set & TIOCM_RI)
		v24_sig |= RFCOMM_V24_IC;
	if (set & TIOCM_CD)
		v24_sig |= RFCOMM_V24_DV;

	if (clear & TIOCM_DSR || clear & TIOCM_DTR)
		v24_sig &= ~RFCOMM_V24_RTC;
	if (clear & TIOCM_RTS || clear & TIOCM_CTS)
		v24_sig &= ~RFCOMM_V24_RTR;
	if (clear & TIOCM_RI)
		v24_sig &= ~RFCOMM_V24_IC;
	if (clear & TIOCM_CD)
		v24_sig &= ~RFCOMM_V24_DV;

	rfcomm_dlc_set_modem_status(dlc, v24_sig);

	return 0;
}