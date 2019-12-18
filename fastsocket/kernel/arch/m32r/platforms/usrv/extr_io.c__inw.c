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
 int /*<<< orphan*/  pcc_ioread_word (int /*<<< orphan*/ ,unsigned long,unsigned short*,int,int,int /*<<< orphan*/ ) ; 

unsigned short _inw(unsigned long port)
{
	if (port >= CFC_IOSTART && port <= CFC_IOEND) {
		unsigned short w;
		pcc_ioread_word(0, port, &w, sizeof(w), 1, 0);
		return w;
	} else
		return *(volatile unsigned short *)PORT2ADDR(port);
}