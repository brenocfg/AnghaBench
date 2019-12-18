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
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t capacity; size_t entry_size; int /*<<< orphan*/  comparator; scalar_t__ size; scalar_t__ entries; } ;
typedef  TYPE_1__ VC_CONTAINERS_LIST_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_COMPARATOR_T ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (size_t) ; 

VC_CONTAINERS_LIST_T *vc_containers_list_create(uint32_t capacity,
      size_t entry_size,
      VC_CONTAINERS_LIST_COMPARATOR_T comparator)
{
   VC_CONTAINERS_LIST_T *list;

   list = (VC_CONTAINERS_LIST_T *)malloc(sizeof(VC_CONTAINERS_LIST_T));
   if (!list)
      return NULL;

   /* Ensure non-zero capacity, as that signifies a read-only list */
   if (!capacity) capacity = 1;

   list->entries = malloc(capacity * entry_size);
   if (!list->entries)
   {
      free(list);
      return NULL;
   }

   list->size = 0;
   list->capacity = capacity;
   list->entry_size = entry_size;
   list->comparator = comparator;

   return list;
}