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
 unsigned int CFC_IOEND ; 
 unsigned int CFC_IOSTART ; 
 unsigned short* PORT2ADDR (unsigned int) ; 
 int /*<<< orphan*/  pcc_iowrite_word (int /*<<< orphan*/ ,unsigned int,void*,int,unsigned long,int) ; 

void _outsw(unsigned int port, const void * addr, unsigned long count)
{
	const unsigned short *buf = addr;
	unsigned short *portp;

	if (port >= CFC_IOSTART && port <= CFC_IOEND)
		pcc_iowrite_word(0, port, (void *)addr, sizeof(unsigned short),
			count, 1);
	else {
		portp = PORT2ADDR(port);
		while (count--)
			*(volatile unsigned short *)portp = *buf++;
	}
}