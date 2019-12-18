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
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 scalar_t__ TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,scalar_t__,int,int,int) ; 
 scalar_t__ host_integerp (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_wide_integer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
dump_array_domain (pretty_printer *buffer, tree domain, int spc, int flags)
{
  pp_character (buffer, '[');
  if (domain)
    {
      tree min = TYPE_MIN_VALUE (domain);
      tree max = TYPE_MAX_VALUE (domain);

      if (min && max
	  && integer_zerop (min)
	  && host_integerp (max, 0))
	pp_wide_integer (buffer, TREE_INT_CST_LOW (max) + 1);
      else
	{
	  if (min)
	    dump_generic_node (buffer, min, spc, flags, false);
	  pp_character (buffer, ':');
	  if (max)
	    dump_generic_node (buffer, max, spc, flags, false);
	}
    }
  else
    pp_string (buffer, "<unknown>");
  pp_character (buffer, ']');
}