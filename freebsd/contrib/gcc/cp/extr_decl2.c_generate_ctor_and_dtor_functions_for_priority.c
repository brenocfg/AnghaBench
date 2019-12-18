#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* splay_tree_node ;
typedef  TYPE_2__* priority_info ;
typedef  int /*<<< orphan*/  location_t ;
struct TYPE_5__ {scalar_t__ destructions_p; scalar_t__ initializations_p; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; scalar_t__ key; } ;

/* Variables and functions */
 int DEFAULT_INIT_PRIORITY ; 
 int /*<<< orphan*/  generate_ctor_or_dtor_function (int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ static_ctors ; 
 scalar_t__ static_dtors ; 

__attribute__((used)) static int
generate_ctor_and_dtor_functions_for_priority (splay_tree_node n, void * data)
{
  location_t *locus = (location_t *) data;
  int priority = (int) n->key;
  priority_info pi = (priority_info) n->value;

  /* Generate the functions themselves, but only if they are really
     needed.  */
  if (pi->initializations_p
      || (priority == DEFAULT_INIT_PRIORITY && static_ctors))
    generate_ctor_or_dtor_function (/*constructor_p=*/true, priority, locus);
  if (pi->destructions_p
      || (priority == DEFAULT_INIT_PRIORITY && static_dtors))
    generate_ctor_or_dtor_function (/*constructor_p=*/false, priority, locus);

  /* Keep iterating.  */
  return 0;
}