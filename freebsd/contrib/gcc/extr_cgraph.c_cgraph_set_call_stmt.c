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
typedef  int /*<<< orphan*/  tree ;
struct cgraph_edge {int /*<<< orphan*/  call_stmt; TYPE_1__* caller; } ;
struct TYPE_2__ {scalar_t__ call_site_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 void** htab_find_slot_with_hash (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_remove_elt_with_hash (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cgraph_set_call_stmt (struct cgraph_edge *e, tree new_stmt)
{
  if (e->caller->call_site_hash)
    {
      htab_remove_elt_with_hash (e->caller->call_site_hash,
				 e->call_stmt,
				 htab_hash_pointer (e->call_stmt));
    }
  e->call_stmt = new_stmt;
  if (e->caller->call_site_hash)
    {
      void **slot;
      slot = htab_find_slot_with_hash (e->caller->call_site_hash,
				       e->call_stmt,
				       htab_hash_pointer
				       (e->call_stmt), INSERT);
      gcc_assert (!*slot);
      *slot = e;
    }
}