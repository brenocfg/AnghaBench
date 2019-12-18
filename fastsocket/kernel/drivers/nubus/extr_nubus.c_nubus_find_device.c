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
struct nubus_dev {unsigned short category; unsigned short type; unsigned short dr_hw; unsigned short dr_sw; struct nubus_dev* next; } ;

/* Variables and functions */
 struct nubus_dev* nubus_devices ; 

struct nubus_dev*
nubus_find_device(unsigned short category,
		  unsigned short type,
		  unsigned short dr_hw,
		  unsigned short dr_sw,
		  const struct nubus_dev* from)
{
	struct nubus_dev* itor =
		from ? from->next : nubus_devices;

	while (itor) {
		if (itor->category == category
		    && itor->type == type
		    && itor->dr_hw == dr_hw
		    && itor->dr_sw == dr_sw)
			return itor;
		itor = itor->next;
	}
	return NULL;
}