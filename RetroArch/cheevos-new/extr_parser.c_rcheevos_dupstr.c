#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; scalar_t__ string; } ;
typedef  TYPE_1__ rcheevos_field_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static const char* rcheevos_dupstr(const rcheevos_field_t* field)
{
   char* string = (char*)malloc(field->length + 1);

   if (!string)
      return NULL;

   memcpy((void*)string, (void*)field->string, field->length);
   string[field->length] = 0;
   return string;
}