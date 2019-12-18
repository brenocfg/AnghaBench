#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct line6_dump_request {int /*<<< orphan*/  wait; int /*<<< orphan*/  in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE6_DUMP_NONE ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void line6_dump_finished(struct line6_dump_request *l6dr)
{
	l6dr->in_progress = LINE6_DUMP_NONE;
	wake_up_interruptible(&l6dr->wait);
}