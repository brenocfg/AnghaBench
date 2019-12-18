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
struct TYPE_4__ {scalar_t__ in_lboards; scalar_t__ in_cheevos; } ;
typedef  TYPE_1__ rcheevos_readud_t ;

/* Variables and functions */
 int rcheevos_new_cheevo (TYPE_1__*) ; 
 int rcheevos_new_lboard (TYPE_1__*) ; 

__attribute__((used)) static int rcheevos_read_end_object(void* userdata)
{
   rcheevos_readud_t* ud = (rcheevos_readud_t*)userdata;

   if (ud->in_cheevos)
      return rcheevos_new_cheevo(ud);

   if (ud->in_lboards)
      return rcheevos_new_lboard(ud);

   return 0;
}