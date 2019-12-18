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
struct value {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  call_function_by_hand (struct value*,int,struct value**) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*) ; 
 struct value* find_function_in_inferior (char*) ; 
 scalar_t__ lookup_minimal_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 int /*<<< orphan*/  target_has_execution ; 
 int /*<<< orphan*/  value_as_long (int /*<<< orphan*/ ) ; 
 struct value* value_coerce_array (struct value*) ; 
 struct value* value_string (char*,scalar_t__) ; 

CORE_ADDR 
lookup_objc_class (char *classname)
{
  struct value * function, *classval;

  if (! target_has_execution)
    {
      /* Can't call into inferior to lookup class.  */
      return 0;
    }

  if (lookup_minimal_symbol("objc_lookUpClass", 0, 0))
    function = find_function_in_inferior("objc_lookUpClass");
  else if (lookup_minimal_symbol ("objc_lookup_class", 0, 0))
    function = find_function_in_inferior("objc_lookup_class");
  else
    {
      complaint (&symfile_complaints, "no way to lookup Objective-C classes");
      return 0;
    }

  classval = value_string (classname, strlen (classname) + 1);
  classval = value_coerce_array (classval);
  return (CORE_ADDR) value_as_long (call_function_by_hand (function, 
							   1, &classval));
}