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
typedef  int tcflag_t ;
struct tty {int t_flags; } ;
struct termios {int c_iflag; int c_oflag; int c_lflag; int c_cflag; } ;

/* Variables and functions */
 int ANYP ; 
 int BRKINT ; 
 int CBREAK ; 
 int CRMOD ; 
 int CS7 ; 
 int CS8 ; 
 int CSIZE ; 
 int DECCTQ ; 
 int ECHO ; 
 int ECHOCTL ; 
 int EVENP ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int IGNBRK ; 
 int IGNCR ; 
 int IGNPAR ; 
 int IMAXBEL ; 
 int INLCR ; 
 int INPCK ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int LITOUT ; 
 int ODDP ; 
 int ONLCR ; 
 int OPOST ; 
 int OXTABS ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int PASS8 ; 
 int RAW ; 
 int TANDEM ; 
 int XTABS ; 

__attribute__((used)) static void
ttcompatsetflags(struct tty *tp, struct termios *t)
{
	int flags = tp->t_flags;
	tcflag_t iflag	= t->c_iflag;
	tcflag_t oflag	= t->c_oflag;
	tcflag_t lflag	= t->c_lflag;
	tcflag_t cflag	= t->c_cflag;

	if (flags & RAW) {
		iflag = IGNBRK;
		lflag &= ~(ECHOCTL|ISIG|ICANON|IEXTEN);
	} else {
		iflag &= ~(PARMRK|IGNPAR|IGNCR|INLCR);
		iflag |= BRKINT|IXON|IMAXBEL;
		lflag |= ISIG|IEXTEN|ECHOCTL;	/* XXX was echoctl on ? */
		if (flags & XTABS)
			oflag |= OXTABS;
		else
			oflag &= ~OXTABS;
		if (flags & CBREAK)
			lflag &= ~ICANON;
		else
			lflag |= ICANON;
		if (flags&CRMOD) {
			iflag |= ICRNL;
			oflag |= ONLCR;
		} else {
			iflag &= ~ICRNL;
			oflag &= ~ONLCR;
		}
	}
	if (flags&ECHO)
		lflag |= ECHO;
	else
		lflag &= ~ECHO;

	cflag &= ~(CSIZE|PARENB);
	if (flags&(RAW|LITOUT|PASS8)) {
		cflag |= CS8;
		if (!(flags&(RAW|PASS8))
		    || (flags&(RAW|PASS8|ANYP)) == (PASS8|ANYP))
			iflag |= ISTRIP;
		else
			iflag &= ~ISTRIP;
		if (flags&(RAW|LITOUT))
			oflag &= ~OPOST;
		else
			oflag |= OPOST;
	} else {
		cflag |= CS7|PARENB;
		iflag |= ISTRIP;
		oflag |= OPOST;
	}
	/* XXX don't set INPCK if RAW or PASS8? */
	if ((flags&(EVENP|ODDP)) == EVENP) {
		iflag |= INPCK;
		cflag &= ~PARODD;
	} else if ((flags&(EVENP|ODDP)) == ODDP) {
		iflag |= INPCK;
		cflag |= PARODD;
	} else
		iflag &= ~INPCK;
	if (flags&TANDEM)
		iflag |= IXOFF;
	else
		iflag &= ~IXOFF;
	if ((flags&DECCTQ) == 0)
		iflag |= IXANY;
	else
		iflag &= ~IXANY;
	t->c_iflag = iflag;
	t->c_oflag = oflag;
	t->c_lflag = lflag;
	t->c_cflag = cflag;
}