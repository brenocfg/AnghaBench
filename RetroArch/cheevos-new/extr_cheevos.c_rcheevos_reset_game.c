#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ active; } ;
typedef  TYPE_2__ rcheevos_lboard_t ;
struct TYPE_7__ {int last; } ;
typedef  TYPE_3__ rcheevos_cheevo_t ;
struct TYPE_5__ {unsigned int core_count; unsigned int unofficial_count; unsigned int lboard_count; } ;
struct TYPE_8__ {TYPE_1__ patchdata; TYPE_2__* lboards; TYPE_3__* unofficial; TYPE_3__* core; } ;

/* Variables and functions */
 TYPE_4__ rcheevos_locals ; 

void rcheevos_reset_game(void)
{
   rcheevos_cheevo_t* cheevo;
   rcheevos_lboard_t* lboard;
   unsigned i;

   cheevo = rcheevos_locals.core;
   for (i = 0; i < rcheevos_locals.patchdata.core_count; i++, cheevo++)
   {
      cheevo->last = 1;
   }

   cheevo = rcheevos_locals.unofficial;
   for (i = 0; i < rcheevos_locals.patchdata.unofficial_count; i++, cheevo++)
   {
      cheevo->last = 1;
   }

   lboard = rcheevos_locals.lboards;
   for (i = 0; i < rcheevos_locals.patchdata.lboard_count; i++, lboard++)
   {
      lboard->active = 0;
   }
}