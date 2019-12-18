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
struct cgraph_node {struct cgraph_edge* callers; } ;
struct cgraph_edge {char const* inline_failed; struct cgraph_edge* next_caller; } ;

/* Variables and functions */
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char const*) ; 

__attribute__((used)) static void
cgraph_set_inline_failed (struct cgraph_node *node, const char *reason)
{
  struct cgraph_edge *e;

  if (dump_file)
    fprintf (dump_file, "Inlining failed: %s\n", reason);
  for (e = node->callers; e; e = e->next_caller)
    if (e->inline_failed)
      e->inline_failed = reason;
}