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
struct TYPE_3__ {scalar_t__ X_add_number; int /*<<< orphan*/  X_add_symbol; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  O_constant ; 
 int /*<<< orphan*/  O_symbol ; 
 scalar_t__ abs_section_offset ; 
 scalar_t__ absolute_section ; 
 scalar_t__ now_seg ; 
 int /*<<< orphan*/  symbol_temp_new_now () ; 

__attribute__((used)) static void
current_location (expressionS *expressionp)
{
  if (now_seg == absolute_section)
    {
      expressionp->X_op = O_constant;
      expressionp->X_add_number = abs_section_offset;
    }
  else
    {
      expressionp->X_op = O_symbol;
      expressionp->X_add_symbol = symbol_temp_new_now ();
      expressionp->X_add_number = 0;
    }
}