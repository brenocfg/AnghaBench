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
struct cgraph_node {struct cgraph_node* next; } ;
typedef  int /*<<< orphan*/ * ipa_methodlist_p ;

/* Variables and functions */
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  ipa_add_method (int /*<<< orphan*/ **,struct cgraph_node*) ; 

ipa_methodlist_p
ipa_methodlist_init (void)
{
  struct cgraph_node *node;
  ipa_methodlist_p wl;

  wl = NULL;
  for (node = cgraph_nodes; node; node = node->next)
    ipa_add_method (&wl, node);

  return wl;
}