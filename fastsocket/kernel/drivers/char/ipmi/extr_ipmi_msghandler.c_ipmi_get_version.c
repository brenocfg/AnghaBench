#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ipmi_user_t ;
struct TYPE_5__ {TYPE_1__* intf; } ;
struct TYPE_4__ {unsigned char ipmi_version_major; unsigned char ipmi_version_minor; } ;

/* Variables and functions */

void ipmi_get_version(ipmi_user_t   user,
		      unsigned char *major,
		      unsigned char *minor)
{
	*major = user->intf->ipmi_version_major;
	*minor = user->intf->ipmi_version_minor;
}