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
struct observer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_observer_detach (int /*<<< orphan*/ *,struct observer*) ; 
 int /*<<< orphan*/  normal_stop_subject ; 

void
observer_detach_normal_stop (struct observer *observer)
{
  generic_observer_detach (&normal_stop_subject, observer);
}