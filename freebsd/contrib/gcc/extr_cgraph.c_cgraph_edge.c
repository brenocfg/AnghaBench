#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ tree ;
struct cgraph_node {scalar_t__ call_site_hash; struct cgraph_edge* callees; } ;
struct cgraph_edge {scalar_t__ call_stmt; struct cgraph_edge* next_callee; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  edge_eq ; 
 int /*<<< orphan*/  edge_hash ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void** htab_find_slot_with_hash (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cgraph_edge* htab_find_with_hash (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (scalar_t__) ; 

struct cgraph_edge *
cgraph_edge (struct cgraph_node *node, tree call_stmt)
{
  struct cgraph_edge *e, *e2;
  int n = 0;

  if (node->call_site_hash)
    return htab_find_with_hash (node->call_site_hash, call_stmt,
      				htab_hash_pointer (call_stmt));

  /* This loop may turn out to be performance problem.  In such case adding
     hashtables into call nodes with very many edges is probably best
     solution.  It is not good idea to add pointer into CALL_EXPR itself
     because we want to make possible having multiple cgraph nodes representing
     different clones of the same body before the body is actually cloned.  */
  for (e = node->callees; e; e= e->next_callee)
    {
      if (e->call_stmt == call_stmt)
	break;
      n++;
    }
  if (n > 100)
    {
      node->call_site_hash = htab_create_ggc (120, edge_hash, edge_eq, NULL);
      for (e2 = node->callees; e2; e2 = e2->next_callee)
	{
          void **slot;
	  slot = htab_find_slot_with_hash (node->call_site_hash,
					   e2->call_stmt,
					   htab_hash_pointer (e2->call_stmt),
					   INSERT);
	  gcc_assert (!*slot);
	  *slot = e2;
	}
    }
  return e;
}