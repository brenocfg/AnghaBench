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
 unsigned long M32R_PCC_IOEND0 ; 
 unsigned long M32R_PCC_IOEND1 ; 
 unsigned long M32R_PCC_IOSTART0 ; 
 unsigned long M32R_PCC_IOSTART1 ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 int /*<<< orphan*/  PORT2ADDR_NE (unsigned long) ; 
 int /*<<< orphan*/  _ne_outw (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_iowrite (int,unsigned long,unsigned short*,int,int,int /*<<< orphan*/ ) ; 

void _outw(unsigned short w, unsigned long port)
{
	if (port >= 0x300 && port < 0x320)
		_ne_outw(w, PORT2ADDR_NE(port));
	else
#if defined(CONFIG_PCMCIA) && defined(CONFIG_M32R_PCC)
	if (port >= M32R_PCC_IOSTART0 && port <= M32R_PCC_IOEND0) {
		pcc_iowrite(0, port, &w, sizeof(w), 1, 0);
	} else 	if (port >= M32R_PCC_IOSTART1 && port <= M32R_PCC_IOEND1) {
		pcc_iowrite(1, port, &w, sizeof(w), 1, 0);
	} else
#endif
		*(volatile unsigned short *)PORT2ADDR(port) = w;
}