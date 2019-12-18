#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {void* controller; int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  PerConfig_struct ;
typedef  int /*<<< orphan*/  PerBaseConfig_struct ;

/* Variables and functions */
 TYPE_1__* perkeyconfig ; 
 int perkeyconfigsize ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 

void PerUpdateConfig(PerBaseConfig_struct * baseconfig, int nelems, void * controller)
{
   u32 oldsize = perkeyconfigsize;
   u32 i, j;

   perkeyconfigsize += nelems;
   perkeyconfig = realloc(perkeyconfig, perkeyconfigsize * sizeof(PerConfig_struct));
   j = 0;
   for(i = oldsize;i < perkeyconfigsize;i++)
   {
      perkeyconfig[i].base = baseconfig + j;
      perkeyconfig[i].controller = controller;
      j++;
   }
}