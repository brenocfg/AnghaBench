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
typedef  int /*<<< orphan*/  w ;

/* Variables and functions */
 unsigned long LAN_IOEND ; 
 unsigned long LAN_IOSTART ; 
 unsigned long M32R_PCC_IOEND0 ; 
 unsigned long M32R_PCC_IOSTART0 ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 int /*<<< orphan*/  PORT2ADDR_NE (unsigned long) ; 
 scalar_t__ PORT2ADDR_USB (unsigned long) ; 
 scalar_t__ __port2addr_ata (unsigned long) ; 
 int /*<<< orphan*/  _ne_outw (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_iowrite_word (int /*<<< orphan*/ ,unsigned long,unsigned short*,int,int,int /*<<< orphan*/ ) ; 

void _outw(unsigned short w, unsigned long port)
{
	if (port >= LAN_IOSTART && port < LAN_IOEND)
		_ne_outw(w, PORT2ADDR_NE(port));
	else
#if defined(CONFIG_IDE) && !defined(CONFIG_M32R_CFC)
	if ((port >= 0x1f0 && port <=0x1f7) || port == 0x3f6) {
		*(volatile unsigned short *)__port2addr_ata(port) = w;
	} else
#endif
#if defined(CONFIG_USB)
	if (port >= 0x340 && port < 0x3a0)
		*(volatile unsigned short *)PORT2ADDR_USB(port) = w;
	else
#endif
#if defined(CONFIG_PCMCIA) && defined(CONFIG_M32R_CFC)
	if (port >= M32R_PCC_IOSTART0 && port <= M32R_PCC_IOEND0) {
		pcc_iowrite_word(0, port, &w, sizeof(w), 1, 0);
	} else
#endif
		*(volatile unsigned short *)PORT2ADDR(port) = w;
}