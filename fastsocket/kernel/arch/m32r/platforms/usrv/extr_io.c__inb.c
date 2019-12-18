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
 unsigned long CFC_IOEND ; 
 unsigned long CFC_IOSTART ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 int /*<<< orphan*/  pcc_ioread_byte (int /*<<< orphan*/ ,unsigned long,unsigned char*,int,int,int /*<<< orphan*/ ) ; 

unsigned char _inb(unsigned long port)
{
	if (port >= CFC_IOSTART && port <= CFC_IOEND) {
		unsigned char b;
		pcc_ioread_byte(0, port, &b, sizeof(b), 1, 0);
		return b;
	} else
		return *(volatile unsigned char *)PORT2ADDR(port);
}