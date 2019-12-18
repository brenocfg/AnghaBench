#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct layout {unsigned int device_id; TYPE_1__* codecs; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 struct layout* layouts ; 

__attribute__((used)) static struct layout *find_layout_by_device(unsigned int id)
{
	struct layout *l;

	l = layouts;
	while (l->codecs[0].name) {
		if (l->device_id == id)
			return l;
		l++;
	}
	return NULL;
}