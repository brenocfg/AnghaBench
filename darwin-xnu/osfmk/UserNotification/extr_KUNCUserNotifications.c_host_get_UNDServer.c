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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  host_priv_t ;
typedef  int /*<<< orphan*/  UNDServerRef ;

/* Variables and functions */
 int /*<<< orphan*/  host_get_user_notification_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
host_get_UNDServer(
	host_priv_t     host_priv,
	UNDServerRef	*serverp)
{
	return (host_get_user_notification_port(host_priv, serverp));
}