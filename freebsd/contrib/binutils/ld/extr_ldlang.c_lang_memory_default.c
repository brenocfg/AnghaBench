#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int not_flags; struct TYPE_7__* next; } ;
typedef  TYPE_1__ lang_memory_region_type ;
typedef  int flagword ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MEMORY_REGION ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_DATA ; 
 int SEC_READONLY ; 
 TYPE_1__* lang_memory_region_list ; 
 TYPE_1__* lang_memory_region_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static lang_memory_region_type *
lang_memory_default (asection *section)
{
  lang_memory_region_type *p;

  flagword sec_flags = section->flags;

  /* Override SEC_DATA to mean a writable section.  */
  if ((sec_flags & (SEC_ALLOC | SEC_READONLY | SEC_CODE)) == SEC_ALLOC)
    sec_flags |= SEC_DATA;

  for (p = lang_memory_region_list; p != NULL; p = p->next)
    {
      if ((p->flags & sec_flags) != 0
	  && (p->not_flags & sec_flags) == 0)
	{
	  return p;
	}
    }
  return lang_memory_region_lookup (DEFAULT_MEMORY_REGION, FALSE);
}