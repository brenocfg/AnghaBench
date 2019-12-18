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
struct ipmi_addr {size_t channel; } ;
typedef  TYPE_2__* ipmi_smi_t ;
struct TYPE_5__ {TYPE_1__* channels; } ;
struct TYPE_4__ {unsigned char lun; unsigned char address; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IPMI_MAX_CHANNELS ; 

__attribute__((used)) static int check_addr(ipmi_smi_t       intf,
		      struct ipmi_addr *addr,
		      unsigned char    *saddr,
		      unsigned char    *lun)
{
	if (addr->channel >= IPMI_MAX_CHANNELS)
		return -EINVAL;
	*lun = intf->channels[addr->channel].lun;
	*saddr = intf->channels[addr->channel].address;
	return 0;
}