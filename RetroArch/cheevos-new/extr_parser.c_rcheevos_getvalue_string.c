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
struct TYPE_2__ {char const* value; size_t length; scalar_t__ is_key; } ;
typedef  TYPE_1__ rcheevos_getvalueud_t ;

/* Variables and functions */

__attribute__((used)) static int rcheevos_getvalue_string(void* userdata,
      const char* string, size_t length)
{
   rcheevos_getvalueud_t* ud = (rcheevos_getvalueud_t*)userdata;

   if (ud->is_key)
   {
      ud->value  = string;
      ud->length = length;
      ud->is_key = 0;
   }

   return 0;
}