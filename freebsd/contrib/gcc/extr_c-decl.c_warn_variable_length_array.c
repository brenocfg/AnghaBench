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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  OPT_Wvla ; 
 int TREE_CONSTANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,...) ; 
 scalar_t__ warn_vla ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
warn_variable_length_array (const char *name, tree size)
{
  int ped = !flag_isoc99 && pedantic && warn_vla != 0;
  int const_size = TREE_CONSTANT (size);

  if (ped)
    {
      if (const_size)
	{
	  if (name)
	    pedwarn ("ISO C90 forbids array %qs whose size "
		     "can%'t be evaluated",
		     name);
	  else
	    pedwarn ("ISO C90 forbids array whose size "
		     "can%'t be evaluated");
	}
      else
	{
	  if (name) 
	    pedwarn ("ISO C90 forbids variable length array %qs",
		     name);
	  else
	    pedwarn ("ISO C90 forbids variable length array");
	}
    }
  else if (warn_vla > 0)
    {
      if (const_size)
        {
	  if (name)
	    warning (OPT_Wvla,
		     "the size of array %qs can"
		     "%'t be evaluated", name);
	  else
	    warning (OPT_Wvla,
		     "the size of array can %'t be evaluated");
	}
      else
	{
	  if (name)
	    warning (OPT_Wvla,
		     "variable length array %qs is used",
		     name);
	  else
	    warning (OPT_Wvla,
		     "variable length array is used");
	}
    }
}