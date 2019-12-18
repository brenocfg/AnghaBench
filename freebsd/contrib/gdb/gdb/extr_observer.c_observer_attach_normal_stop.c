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
typedef  int /*<<< orphan*/  observer_normal_stop_ftype ;

/* Variables and functions */
 struct observer* generic_observer_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  normal_stop_subject ; 
 int /*<<< orphan*/  observer_normal_stop_notification_stub ; 

struct observer *
observer_attach_normal_stop (observer_normal_stop_ftype *f)
{
  return generic_observer_attach (&normal_stop_subject,
				  &observer_normal_stop_notification_stub,
				  (void *) f);
}