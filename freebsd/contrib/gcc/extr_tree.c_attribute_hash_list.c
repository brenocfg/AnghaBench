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
 int /*<<< orphan*/  IDENTIFIER_HASH_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 unsigned int iterative_hash_object (int /*<<< orphan*/ ,unsigned int) ; 

unsigned int
attribute_hash_list (tree list, hashval_t hashcode)
{
  tree tail;

  for (tail = list; tail; tail = TREE_CHAIN (tail))
    /* ??? Do we want to add in TREE_VALUE too? */
    hashcode = iterative_hash_object
      (IDENTIFIER_HASH_VALUE (TREE_PURPOSE (tail)), hashcode);
  return hashcode;
}