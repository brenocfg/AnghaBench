#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; int /*<<< orphan*/ * function; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 TYPE_1__ loopback_timer ; 
 int /*<<< orphan*/  rose_loopback_timer ; 

__attribute__((used)) static void rose_set_loopback_timer(void)
{
	del_timer(&loopback_timer);

	loopback_timer.data     = 0;
	loopback_timer.function = &rose_loopback_timer;
	loopback_timer.expires  = jiffies + 10;

	add_timer(&loopback_timer);
}