#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ io_mem_addr; scalar_t__ io_mem_length; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void release_io_mem(ctlr_info_t *c)
{
	/* if IO mem was not protected do nothing */
	if( c->io_mem_addr == 0)
		return;
	release_region(c->io_mem_addr, c->io_mem_length);
	c->io_mem_addr = 0;
	c->io_mem_length = 0;
}