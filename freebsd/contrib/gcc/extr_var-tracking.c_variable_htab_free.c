#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* variable ;
typedef  TYPE_2__* location_chain ;
struct TYPE_6__ {scalar_t__ refcount; int n_var_parts; TYPE_1__* var_part; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* loc_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  loc_chain_pool ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  var_pool ; 

__attribute__((used)) static void
variable_htab_free (void *elem)
{
  int i;
  variable var = (variable) elem;
  location_chain node, next;

  gcc_assert (var->refcount > 0);

  var->refcount--;
  if (var->refcount > 0)
    return;

  for (i = 0; i < var->n_var_parts; i++)
    {
      for (node = var->var_part[i].loc_chain; node; node = next)
	{
	  next = node->next;
	  pool_free (loc_chain_pool, node);
	}
      var->var_part[i].loc_chain = NULL;
    }
  pool_free (var_pool, var);
}