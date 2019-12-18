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
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 unsigned long LAN_IOEND ; 
 unsigned long LAN_IOSTART ; 
 unsigned long M32R_PCC_IOEND0 ; 
 unsigned long M32R_PCC_IOSTART0 ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 int /*<<< orphan*/  PORT2ADDR_NE (unsigned long) ; 
 scalar_t__ __port2addr_ata (unsigned long) ; 
 int /*<<< orphan*/  _ne_outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_iowrite_byte (int /*<<< orphan*/ ,unsigned long,unsigned char*,int,int,int /*<<< orphan*/ ) ; 

void _outb(unsigned char b, unsigned long port)
{
	if (port >= LAN_IOSTART && port < LAN_IOEND)
		_ne_outb(b, PORT2ADDR_NE(port));
	else
#if defined(CONFIG_IDE) && !defined(CONFIG_M32R_CFC)
	if ((port >= 0x1f0 && port <=0x1f7) || port == 0x3f6) {
		*(volatile unsigned char *)__port2addr_ata(port) = b;
	} else
#endif
#if defined(CONFIG_PCMCIA) && defined(CONFIG_M32R_CFC)
	if (port >= M32R_PCC_IOSTART0 && port <= M32R_PCC_IOEND0) {
		pcc_iowrite_byte(0, port, &b, sizeof(b), 1, 0);
	} else
#endif
		*(volatile unsigned char *)PORT2ADDR(port) = b;
}