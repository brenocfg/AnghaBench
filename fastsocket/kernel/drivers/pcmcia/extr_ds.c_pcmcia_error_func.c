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
struct TYPE_3__ {int key; char const* msg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* service_table ; 

const char *pcmcia_error_func(int func)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(service_table); i++)
		if (service_table[i].key == func)
			return service_table[i].msg;

	return "Unknown service number";
}