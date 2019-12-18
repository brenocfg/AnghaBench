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
struct stlport {int brklen; int uartaddr; } ;

/* Variables and functions */
 int COR2 ; 
 int COR2_ETC ; 
 int EREG_DATA ; 
 int ETC_CMD ; 
 int ETC_STARTBREAK ; 
 int ETC_STOPBREAK ; 
 int SRER ; 
 int SRER_TXDATA ; 
 int SRER_TXEMPTY ; 
 int TDR ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static int stl_cd1400breakisr(struct stlport *portp, int ioaddr)
{
	if (portp->brklen == 1) {
		outb((COR2 + portp->uartaddr), ioaddr);
		outb((inb(ioaddr + EREG_DATA) | COR2_ETC),
			(ioaddr + EREG_DATA));
		outb((TDR + portp->uartaddr), ioaddr);
		outb(ETC_CMD, (ioaddr + EREG_DATA));
		outb(ETC_STARTBREAK, (ioaddr + EREG_DATA));
		outb((SRER + portp->uartaddr), ioaddr);
		outb((inb(ioaddr + EREG_DATA) & ~(SRER_TXDATA | SRER_TXEMPTY)),
			(ioaddr + EREG_DATA));
		return 1;
	} else if (portp->brklen > 1) {
		outb((TDR + portp->uartaddr), ioaddr);
		outb(ETC_CMD, (ioaddr + EREG_DATA));
		outb(ETC_STOPBREAK, (ioaddr + EREG_DATA));
		portp->brklen = -1;
		return 1;
	} else {
		outb((COR2 + portp->uartaddr), ioaddr);
		outb((inb(ioaddr + EREG_DATA) & ~COR2_ETC),
			(ioaddr + EREG_DATA));
		portp->brklen = 0;
	}
	return 0;
}