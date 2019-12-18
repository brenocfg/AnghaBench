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
typedef  int (* walk_namespaces_fn ) (scalar_t__,void*) ;
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ namespaces; } ;

/* Variables and functions */
 TYPE_1__* NAMESPACE_LEVEL (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int stub1 (scalar_t__,void*) ; 

__attribute__((used)) static int
walk_namespaces_r (tree namespace, walk_namespaces_fn f, void* data)
{
  int result = 0;
  tree current = NAMESPACE_LEVEL (namespace)->namespaces;

  result |= (*f) (namespace, data);

  for (; current; current = TREE_CHAIN (current))
    result |= walk_namespaces_r (current, f, data);

  return result;
}