#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* ipmi_user_t ;
struct TYPE_7__ {TYPE_2__* intf; } ;
struct TYPE_6__ {TYPE_1__* channels; } ;
struct TYPE_5__ {unsigned char lun; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IPMI_MAX_CHANNELS ; 

int ipmi_get_my_LUN(ipmi_user_t   user,
		    unsigned int  channel,
		    unsigned char *address)
{
	if (channel >= IPMI_MAX_CHANNELS)
		return -EINVAL;
	*address = user->intf->channels[channel].lun;
	return 0;
}