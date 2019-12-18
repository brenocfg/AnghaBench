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
struct cgraph_node {struct cgraph_node* master_clone; int /*<<< orphan*/  decl; } ;
typedef  enum availability { ____Placeholder_availability } availability ;

/* Variables and functions */
 int AVAIL_NOT_AVAILABLE ; 
 int AVAIL_OVERWRITABLE ; 
 int cgraph_function_body_availability (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_node (int /*<<< orphan*/ ) ; 

struct cgraph_node *
cgraph_master_clone (struct cgraph_node *n)
{
  enum availability avail = cgraph_function_body_availability (n);

  if (avail == AVAIL_NOT_AVAILABLE || avail == AVAIL_OVERWRITABLE)
    return NULL;

  if (!n->master_clone)
    n->master_clone = cgraph_node (n->decl);

  return n->master_clone;
}