#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* htab_t ;
struct TYPE_7__ {scalar_t__* slot; scalar_t__* limit; TYPE_1__* htab; } ;
typedef  TYPE_2__ htab_iterator ;
struct TYPE_6__ {scalar_t__* entries; } ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 scalar_t__ HTAB_DELETED_ENTRY ; 
 scalar_t__ HTAB_EMPTY_ENTRY ; 
 int htab_size (TYPE_1__*) ; 

__attribute__((used)) static inline void *
first_htab_element (htab_iterator *hti, htab_t table)
{
  hti->htab = table;
  hti->slot = table->entries;
  hti->limit = hti->slot + htab_size (table);
  do
    {
      PTR x = *(hti->slot);
      if (x != HTAB_EMPTY_ENTRY && x != HTAB_DELETED_ENTRY)
	break;
    } while (++(hti->slot) < hti->limit);
  
  if (hti->slot < hti->limit)
    return *(hti->slot);
  return NULL;
}