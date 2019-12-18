#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ io_mem_addr; } ;
typedef  TYPE_1__ ctlr_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  busaddr; } ;
typedef  TYPE_2__ cmdlist_t ;

/* Variables and functions */
 scalar_t__ COMMAND_FIFO ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void smart2e_submit_command(ctlr_info_t *h, cmdlist_t *c)
{
	outl(c->busaddr, h->io_mem_addr + COMMAND_FIFO);
}