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
struct socket {int dummy; } ;
typedef  int /*<<< orphan*/  sflt_handle ;
typedef  int /*<<< orphan*/  sflt_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  sflt_notify_internal (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sflt_notify_after_register(struct socket *so, sflt_event_t event,
    sflt_handle handle)
{
	sflt_notify_internal(so, event, NULL, handle);
}