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
struct TYPE_2__ {void (* function ) (unsigned long) ;unsigned long data; scalar_t__ expires; } ;
struct line6_dump_request {TYPE_1__ timer; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

void line6_startup_delayed(struct line6_dump_request *l6dr, int seconds,
			   void (*function)(unsigned long), void *data)
{
	l6dr->timer.expires = jiffies + seconds * HZ;
	l6dr->timer.function = function;
	l6dr->timer.data = (unsigned long)data;
	add_timer(&l6dr->timer);
}