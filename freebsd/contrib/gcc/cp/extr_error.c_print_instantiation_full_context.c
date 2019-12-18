#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;
struct TYPE_4__ {int /*<<< orphan*/  printer; } ;
typedef  TYPE_1__ diagnostic_context ;

/* Variables and functions */
 int /*<<< orphan*/  LOCATION_FILE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 int TFF_DECL_SPECIFIERS ; 
 int TFF_RETURN_TYPE ; 
 scalar_t__ TINST_DECL (scalar_t__) ; 
 int /*<<< orphan*/  TINST_LOCATION (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ current_function_decl ; 
 scalar_t__ current_instantiation () ; 
 int /*<<< orphan*/  decl_as_string (scalar_t__,int) ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  pp_verbatim (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_instantiation_partial_context (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_instantiation_full_context (diagnostic_context *context)
{
  tree p = current_instantiation ();
  location_t location = input_location;

  if (p)
    {
      if (current_function_decl != TINST_DECL (p)
	  && current_function_decl != NULL_TREE)
	/* We can get here during the processing of some synthesized
	   method.  Then, TINST_DECL (p) will be the function that's causing
	   the synthesis.  */
	;
      else
	{
	  if (current_function_decl == TINST_DECL (p))
	    /* Avoid redundancy with the "In function" line.  */;
	  else
	    pp_verbatim (context->printer,
			 "%s: In instantiation of %qs:\n",
			 LOCATION_FILE (location),
			 decl_as_string (TINST_DECL (p),
					 TFF_DECL_SPECIFIERS | TFF_RETURN_TYPE));

	  location = TINST_LOCATION (p);
	  p = TREE_CHAIN (p);
	}
    }

  print_instantiation_partial_context (context, p, location);
}