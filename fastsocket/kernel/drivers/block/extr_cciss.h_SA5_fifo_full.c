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
struct TYPE_3__ {scalar_t__ commands_outstanding; scalar_t__ max_commands; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */

__attribute__((used)) static unsigned long SA5_fifo_full(ctlr_info_t *h)
{
	if( h->commands_outstanding >= h->max_commands)
		return(1);
	else 
		return(0);

}