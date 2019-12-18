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
typedef  int phys_addr ;

/* Variables and functions */
 scalar_t__ IOADDR ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static inline void
PORT(phys_addr a, unsigned int cmd) {
	if (a & 0xf)
		printk("lp486e.c: PORT: address not aligned\n");
	outw(((a & 0xffff) | cmd), IOADDR);
	outw(((a>>16) & 0xffff), IOADDR+2);
}