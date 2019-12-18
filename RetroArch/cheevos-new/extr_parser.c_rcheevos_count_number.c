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
struct TYPE_2__ {scalar_t__ field_hash; int /*<<< orphan*/  lboard_count; scalar_t__ in_lboards; int /*<<< orphan*/  unofficial_count; int /*<<< orphan*/  core_count; scalar_t__ in_cheevos; } ;
typedef  TYPE_1__ rcheevos_countud_t ;

/* Variables and functions */
 scalar_t__ CHEEVOS_JSON_KEY_FLAGS ; 
 scalar_t__ CHEEVOS_JSON_KEY_ID ; 
 long strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rcheevos_count_number(void* userdata,
      const char* number, size_t length)
{
   rcheevos_countud_t* ud = (rcheevos_countud_t*)userdata;

   if (ud->in_cheevos && ud->field_hash == CHEEVOS_JSON_KEY_FLAGS)
   {
      long flags = strtol(number, NULL, 10);

      if (flags == 3)
         ud->core_count++;       /* Core achievements */
      else if (flags == 5)
         ud->unofficial_count++; /* Unofficial achievements */
   }
   else if (ud->in_lboards && ud->field_hash == CHEEVOS_JSON_KEY_ID)
      ud->lboard_count++;

   return 0;
}