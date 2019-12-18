#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ vid; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* ch7xxx_ids ; 

__attribute__((used)) static char *ch7xxx_get_id(uint8_t vid)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ch7xxx_ids); i++) {
		if (ch7xxx_ids[i].vid == vid)
			return ch7xxx_ids[i].name;
	}

	return NULL;
}