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
struct TYPE_2__ {scalar_t__ field_hash; int in_cheevos; int in_lboards; } ;
typedef  TYPE_1__ rcheevos_countud_t ;

/* Variables and functions */
 scalar_t__ CHEEVOS_JSON_KEY_ACHIEVEMENTS ; 
 scalar_t__ CHEEVOS_JSON_KEY_LEADERBOARDS ; 
 scalar_t__ rcheevos_djb2 (char const*,size_t) ; 

__attribute__((used)) static int rcheevos_count_key(void* userdata,
      const char* name, size_t length)
{
   rcheevos_countud_t* ud = (rcheevos_countud_t*)userdata;

   ud->field_hash        = rcheevos_djb2(name, length);

   if (ud->field_hash == CHEEVOS_JSON_KEY_ACHIEVEMENTS)
      ud->in_cheevos     = 1;
   else if (ud->field_hash == CHEEVOS_JSON_KEY_LEADERBOARDS)
      ud->in_lboards     = 1;

   return 0;
}