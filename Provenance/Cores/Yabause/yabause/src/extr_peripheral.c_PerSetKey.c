#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {void* controller; int /*<<< orphan*/  key; TYPE_1__* base; } ;
struct TYPE_3__ {scalar_t__ name; } ;

/* Variables and functions */
 TYPE_2__* perkeyconfig ; 
 unsigned int perkeyconfigsize ; 

void PerSetKey(u32 key, u8 name, void * controller)
{
	unsigned int i = 0;

	while(i < perkeyconfigsize)
	{
		if ((name == perkeyconfig[i].base->name) && (controller == perkeyconfig[i].controller))
		{
			perkeyconfig[i].key = key;
		}
		i++;
	}
}