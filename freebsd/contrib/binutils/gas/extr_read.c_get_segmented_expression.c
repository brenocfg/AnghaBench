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
typedef  int /*<<< orphan*/  segT ;
struct TYPE_4__ {scalar_t__ X_op; scalar_t__ X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 scalar_t__ O_absent ; 
 scalar_t__ O_big ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_illegal ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expression (TYPE_1__*) ; 

__attribute__((used)) static segT
get_segmented_expression (register expressionS *expP)
{
  register segT retval;

  retval = expression (expP);
  if (expP->X_op == O_illegal
      || expP->X_op == O_absent
      || expP->X_op == O_big)
    {
      as_bad (_("expected address expression"));
      expP->X_op = O_constant;
      expP->X_add_number = 0;
      retval = absolute_section;
    }
  return retval;
}