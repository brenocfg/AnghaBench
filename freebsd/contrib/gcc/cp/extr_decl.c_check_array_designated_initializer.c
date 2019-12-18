#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ index; } ;
typedef  TYPE_1__ constructor_elt ;

/* Variables and functions */
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static bool
check_array_designated_initializer (const constructor_elt *ce)
{
  /* Designated initializers for array elements arenot supported.  */
  if (ce->index)
    {
      /* The parser only allows identifiers as designated
	 intializers.  */
      gcc_assert (TREE_CODE (ce->index) == IDENTIFIER_NODE);
      error ("name %qD used in a GNU-style designated "
	     "initializer for an array", ce->index);
      return false;
    }

  return true;
}