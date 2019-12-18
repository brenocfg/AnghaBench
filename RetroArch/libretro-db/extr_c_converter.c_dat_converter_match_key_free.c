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
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* value; } ;
typedef  TYPE_1__ dat_converter_match_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void dat_converter_match_key_free(dat_converter_match_key_t* match_key)
{
   if (!match_key)
      return;

   free(match_key->value);

   while (match_key)
   {
      dat_converter_match_key_t* next = match_key->next;
      free(match_key);
      match_key = next;
   }
}