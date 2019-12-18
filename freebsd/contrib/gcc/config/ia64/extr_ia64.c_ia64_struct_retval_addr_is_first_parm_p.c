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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BLKmode ; 
 scalar_t__ TREE_ADDRESSABLE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MODE (scalar_t__) ; 
 scalar_t__ abi_version_at_least (int) ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
ia64_struct_retval_addr_is_first_parm_p (tree fntype)
{
  tree ret_type = TREE_TYPE (fntype);

  /* The Itanium C++ ABI requires that out0, rather than r8, be used
     as the structure return address parameter, if the return value
     type has a non-trivial copy constructor or destructor.  It is not
     clear if this same convention should be used for other
     programming languages.  Until G++ 3.4, we incorrectly used r8 for
     these return values.  */
  return (abi_version_at_least (2)
	  && ret_type
	  && TYPE_MODE (ret_type) == BLKmode 
	  && TREE_ADDRESSABLE (ret_type)
	  && strcmp (lang_hooks.name, "GNU C++") == 0);
}