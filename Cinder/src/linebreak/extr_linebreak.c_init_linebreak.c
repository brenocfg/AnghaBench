#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ prop; int start; } ;
struct TYPE_3__ {int end; TYPE_2__* lbp; } ;

/* Variables and functions */
 scalar_t__ LBP_Undefined ; 
 size_t LINEBREAK_INDEX_SIZE ; 
 TYPE_2__* lb_prop_default ; 
 TYPE_1__* lb_prop_index ; 

void init_linebreak(void)
{
	size_t i;
	size_t iPropDefault;
	size_t len;
	size_t step;

	len = 0;
	while (lb_prop_default[len].prop != LBP_Undefined)
		++len;
	step = len / LINEBREAK_INDEX_SIZE;
	iPropDefault = 0;
	for (i = 0; i < LINEBREAK_INDEX_SIZE; ++i)
	{
		lb_prop_index[i].lbp = lb_prop_default + iPropDefault;
		iPropDefault += step;
		lb_prop_index[i].end = lb_prop_default[iPropDefault].start - 1;
	}
	lb_prop_index[--i].end = 0xFFFFFFFF;
}