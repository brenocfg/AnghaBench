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
typedef  int count ;
struct TYPE_3__ {int expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int jiffies ; 
 TYPE_1__ seq_timer ; 

void request_sound_timer(int count)
{
	extern unsigned long seq_time;

	if (count < 0) {
		seq_timer.expires = (-count) + jiffies;
		add_timer(&seq_timer);
		return;
	}
	count += seq_time;

	count -= jiffies;

	if (count < 1)
		count = 1;

	seq_timer.expires = (count) + jiffies;
	add_timer(&seq_timer);
}