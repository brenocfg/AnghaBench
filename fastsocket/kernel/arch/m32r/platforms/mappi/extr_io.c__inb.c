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
 unsigned long M32R_PCC_IOEND0 ; 
 unsigned long M32R_PCC_IOEND1 ; 
 unsigned long M32R_PCC_IOSTART0 ; 
 unsigned long M32R_PCC_IOSTART1 ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 int /*<<< orphan*/  PORT2ADDR_NE (unsigned long) ; 
 unsigned char _ne_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_ioread (int,unsigned long,unsigned char*,int,int,int /*<<< orphan*/ ) ; 

unsigned char _inb(unsigned long port)
{
	if (port >= 0x300 && port < 0x320)
		return _ne_inb(PORT2ADDR_NE(port));
	else
#if defined(CONFIG_PCMCIA) && defined(CONFIG_M32R_PCC)
        if (port >= M32R_PCC_IOSTART0 && port <= M32R_PCC_IOEND0) {
		unsigned char b;
		pcc_ioread(0, port, &b, sizeof(b), 1, 0);
		return b;
	} else 	if (port >= M32R_PCC_IOSTART1 && port <= M32R_PCC_IOEND1) {
		unsigned char b;
		pcc_ioread(1, port, &b, sizeof(b), 1, 0);
		return b;
	} else
#endif

	return *(volatile unsigned char *)PORT2ADDR(port);
}