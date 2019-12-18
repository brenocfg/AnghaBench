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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ key; int /*<<< orphan*/  controller; TYPE_1__* base; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* SetAxisValue ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* perkeyconfig ; 
 unsigned int perkeyconfigsize ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PerAxisValue(u32 key, u8 val)
{
   unsigned int i = 0;

   while(i < perkeyconfigsize)
   {
      if (key == perkeyconfig[i].key)
      {
         if (perkeyconfig[i].base->SetAxisValue)
            perkeyconfig[i].base->SetAxisValue(perkeyconfig[i].controller, val);
      }
      i++;
   }
}