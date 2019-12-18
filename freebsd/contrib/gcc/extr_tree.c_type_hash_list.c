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
typedef  unsigned int hashval_t ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_HASH (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 unsigned int iterative_hash_object (int /*<<< orphan*/ ,unsigned int) ; 

unsigned int
type_hash_list (tree list, hashval_t hashcode)
{
  tree tail;

  for (tail = list; tail; tail = TREE_CHAIN (tail))
    if (TREE_VALUE (tail) != error_mark_node)
      hashcode = iterative_hash_object (TYPE_HASH (TREE_VALUE (tail)),
					hashcode);

  return hashcode;
}