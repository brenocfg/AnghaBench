#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ is_console_id; TYPE_1__* patchdata; TYPE_2__* field; } ;
typedef  TYPE_3__ rcheevos_readud_t ;
struct TYPE_5__ {char const* string; size_t length; } ;
struct TYPE_4__ {unsigned int console_id; } ;

/* Variables and functions */
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rcheevos_read_number(void* userdata,
      const char* number, size_t length)
{
   rcheevos_readud_t* ud = (rcheevos_readud_t*)userdata;

   if (ud->field)
   {
      ud->field->string = number;
      ud->field->length = length;
   }
   else if (ud->is_console_id)
   {
      ud->patchdata->console_id = (unsigned)strtol(number, NULL, 10);
      ud->is_console_id         = 0;
   }

   return 0;
}