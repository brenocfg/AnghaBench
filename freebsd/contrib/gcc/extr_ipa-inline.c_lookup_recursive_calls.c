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
struct cgraph_node {struct cgraph_edge* callees; } ;
struct cgraph_edge {int count; struct cgraph_node* callee; int /*<<< orphan*/  inline_failed; struct cgraph_edge* next_callee; } ;
typedef  int /*<<< orphan*/  fibheap_t ;

/* Variables and functions */
 int /*<<< orphan*/  fibheap_insert (int /*<<< orphan*/ ,int,struct cgraph_edge*) ; 
 int max_count ; 

__attribute__((used)) static void
lookup_recursive_calls (struct cgraph_node *node, struct cgraph_node *where,
			fibheap_t heap)
{
  static int priority;
  struct cgraph_edge *e;
  for (e = where->callees; e; e = e->next_callee)
    if (e->callee == node)
      {
	/* When profile feedback is available, prioritize by expected number
	   of calls.  Without profile feedback we maintain simple queue
	   to order candidates via recursive depths.  */
        fibheap_insert (heap,
			!max_count ? priority++
		        : -(e->count / ((max_count + (1<<24) - 1) / (1<<24))),
		        e);
      }
  for (e = where->callees; e; e = e->next_callee)
    if (!e->inline_failed)
      lookup_recursive_calls (node, e->callee, heap);
}