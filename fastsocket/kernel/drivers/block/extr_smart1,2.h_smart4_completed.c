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
 scalar_t__ S42XX_REPLY_PORT_OFFSET ; 
 long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned long smart4_completed(ctlr_info_t *h)
{
	long register_value 
		= readl(h->vaddr + S42XX_REPLY_PORT_OFFSET);

	/* Fifo is empty */
	if( register_value == 0xffffffff)
		return 0; 	

	/* Need to let it know we got the reply */
	/* We do this by writing a 0 to the port we just read from */
	writel(0, h->vaddr + S42XX_REPLY_PORT_OFFSET);

	return ((unsigned long) register_value); 
}