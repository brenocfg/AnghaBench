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
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  UNDServerRef ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ host_get_user_notification_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_priv_self () ; 

__attribute__((used)) static UNDServerRef
UNDServer_reference(void)
{
	UNDServerRef UNDServer;
	kern_return_t kr;

	kr = host_get_user_notification_port(host_priv_self(), &UNDServer);
	assert(kr == KERN_SUCCESS);
	return UNDServer;
}