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
struct uio_mem {int addr; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t map_offset_show(struct uio_mem *mem, char *buf)
{
	return sprintf(buf, "0x%lx\n", mem->addr & ~PAGE_MASK);
}