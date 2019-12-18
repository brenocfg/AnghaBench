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

/* Variables and functions */
 unsigned int M32R_PCC_IOEND0 ; 
 unsigned int M32R_PCC_IOEND1 ; 
 unsigned int M32R_PCC_IOSTART0 ; 
 unsigned int M32R_PCC_IOSTART1 ; 
 unsigned char* PORT2ADDR (unsigned int) ; 
 unsigned char* PORT2ADDR_NE (unsigned int) ; 
 int /*<<< orphan*/  _ne_outb (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  pcc_iowrite (int,unsigned int,void*,int,unsigned long,int) ; 

void _outsb(unsigned int port, const void *addr, unsigned long count)
{
	const unsigned char *buf = addr;
	unsigned char *portp;

	if (port >= 0x300 && port < 0x320) {
		portp = PORT2ADDR_NE(port);
		while (count--)
			_ne_outb(*buf++, portp);
#if defined(CONFIG_PCMCIA) && defined(CONFIG_M32R_PCC)
	} else if (port >= M32R_PCC_IOSTART0 && port <= M32R_PCC_IOEND0) {
		pcc_iowrite(0, port, (void *)addr, sizeof(unsigned char),
			    count, 1);
	} else if (port >= M32R_PCC_IOSTART1 && port <= M32R_PCC_IOEND1) {
		pcc_iowrite(1, port, (void *)addr, sizeof(unsigned char),
			    count, 1);
#endif
	} else {
		portp = PORT2ADDR(port);
		while (count--)
			*(volatile unsigned char *)portp = *buf++;
	}
}