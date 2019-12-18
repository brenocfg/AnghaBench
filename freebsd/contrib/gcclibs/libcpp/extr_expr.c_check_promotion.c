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
struct TYPE_2__ {scalar_t__ unsignedp; } ;
struct op {int /*<<< orphan*/  token; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 int /*<<< orphan*/  CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_token_as_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_positive (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  precision ; 

__attribute__((used)) static void
check_promotion (cpp_reader *pfile, const struct op *op)
{
  if (op->value.unsignedp == op[-1].value.unsignedp)
    return;

  if (op->value.unsignedp)
    {
      if (!num_positive (op[-1].value, CPP_OPTION (pfile, precision)))
	cpp_error (pfile, CPP_DL_WARNING,
		   "the left operand of \"%s\" changes sign when promoted",
		   cpp_token_as_text (pfile, op->token));
    }
  else if (!num_positive (op->value, CPP_OPTION (pfile, precision)))
    cpp_error (pfile, CPP_DL_WARNING,
	       "the right operand of \"%s\" changes sign when promoted",
	       cpp_token_as_text (pfile, op->token));
}