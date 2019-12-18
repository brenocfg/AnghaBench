#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* add_compare ) (unsigned long) ;} ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ stub1 (unsigned long) ; 
 TYPE_1__* tick_ops ; 

__attribute__((used)) static int sparc64_next_event(unsigned long delta,
			      struct clock_event_device *evt)
{
	return tick_ops->add_compare(delta) ? -ETIME : 0;
}