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
struct TYPE_3__ {scalar_t__ vaddr; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */
 scalar_t__ S42XX_REQUEST_PORT_OFFSET ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static unsigned long smart4_fifo_full(ctlr_info_t *h)
{
	
        return (!readl(h->vaddr + S42XX_REQUEST_PORT_OFFSET));
}