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
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int LIMIT ; 
 scalar_t__ NULL_TREE ; 
 size_t SSA_NAME_VERSION (scalar_t__) ; 
 TYPE_1__* copy_of ; 

__attribute__((used)) static tree
get_last_copy_of (tree var)
{
  tree last;
  int i;

  /* Traverse COPY_OF starting at VAR until we get to the last
     link in the chain.  Since it is possible to have cycles in PHI
     nodes, the copy-of chain may also contain cycles.
     
     To avoid infinite loops and to avoid traversing lengthy copy-of
     chains, we artificially limit the maximum number of chains we are
     willing to traverse.

     The value 5 was taken from a compiler and runtime library
     bootstrap and a mixture of C and C++ code from various sources.
     More than 82% of all copy-of chains were shorter than 5 links.  */
#define LIMIT	5

  last = var;
  for (i = 0; i < LIMIT; i++)
    {
      tree copy = copy_of[SSA_NAME_VERSION (last)].value;
      if (copy == NULL_TREE || copy == last)
	break;
      last = copy;
    }

  /* If we have reached the limit, then we are either in a copy-of
     cycle or the copy-of chain is too long.  In this case, just
     return VAR so that it is not considered a copy of anything.  */
  return (i < LIMIT ? last : var);
}