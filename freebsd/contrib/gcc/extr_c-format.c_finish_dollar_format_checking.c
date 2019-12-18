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
struct TYPE_3__ {int /*<<< orphan*/  number_dollar_extra_args; int /*<<< orphan*/  number_other; } ;
typedef  TYPE_1__ format_check_results ;

/* Variables and functions */
 int /*<<< orphan*/  OPT_Wformat ; 
 int dollar_arguments_count ; 
 scalar_t__* dollar_arguments_pointer_p ; 
 int /*<<< orphan*/ * dollar_arguments_used ; 
 scalar_t__ dollar_first_arg_num ; 
 int dollar_max_arg_used ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void
finish_dollar_format_checking (format_check_results *res, int pointer_gap_ok)
{
  int i;
  bool found_pointer_gap = false;
  for (i = 0; i < dollar_max_arg_used; i++)
    {
      if (!dollar_arguments_used[i])
	{
	  if (pointer_gap_ok && (dollar_first_arg_num == 0
				 || dollar_arguments_pointer_p[i]))
	    found_pointer_gap = true;
	  else
	    warning (OPT_Wformat,
		     "format argument %d unused before used argument %d in $-style format",
		     i + 1, dollar_max_arg_used);
	}
    }
  if (found_pointer_gap
      || (dollar_first_arg_num
	  && dollar_max_arg_used < dollar_arguments_count))
    {
      res->number_other--;
      res->number_dollar_extra_args++;
    }
}