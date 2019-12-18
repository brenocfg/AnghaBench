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
typedef  scalar_t__ segT ;
struct TYPE_4__ {scalar_t__ X_add_number; int /*<<< orphan*/  X_op; int /*<<< orphan*/ * X_add_symbol; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  O_constant ; 
 scalar_t__ SEG_NORMAL (scalar_t__) ; 
 int /*<<< orphan*/  S_GET_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,...) ; 
 scalar_t__ expr_section ; 
 scalar_t__ get_segmented_expression (TYPE_1__*) ; 
 int /*<<< orphan*/  know (int) ; 
 scalar_t__ undefined_section ; 

__attribute__((used)) static segT
get_known_segmented_expression (register expressionS *expP)
{
  register segT retval;

  if ((retval = get_segmented_expression (expP)) == undefined_section)
    {
      /* There is no easy way to extract the undefined symbol from the
	 expression.  */
      if (expP->X_add_symbol != NULL
	  && S_GET_SEGMENT (expP->X_add_symbol) != expr_section)
	as_warn (_("symbol \"%s\" undefined; zero assumed"),
		 S_GET_NAME (expP->X_add_symbol));
      else
	as_warn (_("some symbol undefined; zero assumed"));
      retval = absolute_section;
      expP->X_op = O_constant;
      expP->X_add_number = 0;
    }
  know (retval == absolute_section || SEG_NORMAL (retval));
  return (retval);
}