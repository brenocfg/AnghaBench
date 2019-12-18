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
 unsigned long CFC_IOEND ; 
 unsigned long CFC_IOSTART ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 int /*<<< orphan*/  pcc_iowrite_word (int /*<<< orphan*/ ,unsigned long,unsigned short*,int,int,int /*<<< orphan*/ ) ; 

void _outw(unsigned short w, unsigned long port)
{
	if (port >= CFC_IOSTART && port <= CFC_IOEND)
		pcc_iowrite_word(0, port, &w, sizeof(w), 1, 0);
	else
		*(volatile unsigned short *)PORT2ADDR(port) = w;
}