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
struct TYPE_3__ {scalar_t__ io_mem_addr; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */
 scalar_t__ COMMAND_FIFO ; 
 unsigned long inl (scalar_t__) ; 

__attribute__((used)) static unsigned long smart2e_fifo_full(ctlr_info_t *h)
{
	return inl(h->io_mem_addr + COMMAND_FIFO);
}