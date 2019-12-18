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
struct TYPE_2__ {void* sram; int /*<<< orphan*/  on; } ;

/* Variables and functions */
#define  RETRO_MEMORY_SAVE_RAM 128 
 TYPE_1__ sram ; 

void *retro_get_memory_data(unsigned id)
{
   if (!sram.on)
      return NULL;

   switch (id)
   {
      case RETRO_MEMORY_SAVE_RAM:
         return sram.sram;

      default:
         return NULL;
   }
}