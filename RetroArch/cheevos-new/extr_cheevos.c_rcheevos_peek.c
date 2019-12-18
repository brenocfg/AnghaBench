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
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  console_id; } ;
struct TYPE_4__ {TYPE_1__ patchdata; int /*<<< orphan*/  fixups; } ;

/* Variables and functions */
 int* rcheevos_fixup_find (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_2__ rcheevos_locals ; 

__attribute__((used)) static unsigned rcheevos_peek(unsigned address, unsigned num_bytes, void* ud)
{
   const uint8_t* data = rcheevos_fixup_find(&rcheevos_locals.fixups,
      address, rcheevos_locals.patchdata.console_id);
   unsigned value = 0;

   if (data)
   {
      switch (num_bytes)
      {
         case 4: value |= data[2] << 16 | data[3] << 24;
         case 2: value |= data[1] << 8;
         case 1: value |= data[0];
      }
   }

   return value;
}