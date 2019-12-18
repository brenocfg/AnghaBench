#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int dirty; int count; int capacity; TYPE_2__* elements; } ;
typedef  TYPE_1__ rcheevos_fixups_t ;
struct TYPE_9__ {unsigned int address; int /*<<< orphan*/  const* location; } ;
typedef  TYPE_2__ rcheevos_fixup_t ;

/* Variables and functions */
 scalar_t__ bsearch (TYPE_2__*,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcheevos_cmpaddr ; 
 int /*<<< orphan*/ * rcheevos_patch_address (unsigned int,int) ; 
 scalar_t__ realloc (TYPE_2__*,unsigned int) ; 

const uint8_t* rcheevos_fixup_find(rcheevos_fixups_t* fixups, unsigned address, int console)
{
   rcheevos_fixup_t key;
   rcheevos_fixup_t* found;
   const uint8_t* location;

   if (fixups->dirty)
   {
      qsort(fixups->elements, fixups->count, sizeof(rcheevos_fixup_t), rcheevos_cmpaddr);
      fixups->dirty = false;
   }

   key.address = address;
   found = (rcheevos_fixup_t*)bsearch(&key, fixups->elements, fixups->count, sizeof(rcheevos_fixup_t), rcheevos_cmpaddr);

   if (found != NULL)
   {
      return found->location;
   }

   if (fixups->count == fixups->capacity)
   {
      unsigned new_capacity = fixups->capacity == 0 ? 16 : fixups->capacity * 2;
      rcheevos_fixup_t* new_elements = (rcheevos_fixup_t*)
         realloc(fixups->elements, new_capacity * sizeof(rcheevos_fixup_t));

      if (new_elements == NULL)
      {
         return NULL;
      }

      fixups->elements = new_elements;
      fixups->capacity = new_capacity;
   }

   fixups->elements[fixups->count].address = address;
   fixups->elements[fixups->count++].location = location =
      rcheevos_patch_address(address, console);
   fixups->dirty = true;

   return location;
}