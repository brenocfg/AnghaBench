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
struct cgraph_edge {int /*<<< orphan*/  call_stmt; TYPE_1__* caller; TYPE_2__* next_callee; TYPE_3__* prev_callee; } ;
struct TYPE_6__ {TYPE_2__* next_callee; } ;
struct TYPE_5__ {TYPE_3__* prev_callee; } ;
struct TYPE_4__ {scalar_t__ call_site_hash; TYPE_2__* callees; } ;

/* Variables and functions */
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_remove_elt_with_hash (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
cgraph_edge_remove_caller (struct cgraph_edge *e)
{
  if (e->prev_callee)
    e->prev_callee->next_callee = e->next_callee;
  if (e->next_callee)
    e->next_callee->prev_callee = e->prev_callee;
  if (!e->prev_callee)
    e->caller->callees = e->next_callee;
  if (e->caller->call_site_hash)
    htab_remove_elt_with_hash (e->caller->call_site_hash,
			       e->call_stmt,
	  		       htab_hash_pointer (e->call_stmt));
}