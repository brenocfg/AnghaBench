#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
struct TYPE_15__ {int /*<<< orphan*/  skip_eval; } ;
struct TYPE_16__ {TYPE_1__ state; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_17__ {int overflow; int unsignedp; int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  TYPE_3__ cpp_num ;

/* Variables and functions */
#define  CPP_COMPL 130 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 int /*<<< orphan*/  CPP_OPTION (TYPE_2__*,int /*<<< orphan*/ ) ; 
#define  CPP_UMINUS 129 
#define  CPP_UPLUS 128 
 int /*<<< orphan*/  CPP_WTRADITIONAL (TYPE_2__*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ num_negate (TYPE_3__,int /*<<< orphan*/ ) ; 
 TYPE_3__ num_trim (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_zerop (TYPE_3__) ; 
 int /*<<< orphan*/  precision ; 

__attribute__((used)) static cpp_num
num_unary_op (cpp_reader *pfile, cpp_num num, enum cpp_ttype op)
{
  switch (op)
    {
    case CPP_UPLUS:
      if (CPP_WTRADITIONAL (pfile) && !pfile->state.skip_eval)
	cpp_error (pfile, CPP_DL_WARNING,
		   "traditional C rejects the unary plus operator");
      num.overflow = false;
      break;

    case CPP_UMINUS:
      num = num_negate (num, CPP_OPTION (pfile, precision));
      break;

    case CPP_COMPL:
      num.high = ~num.high;
      num.low = ~num.low;
      num = num_trim (num, CPP_OPTION (pfile, precision));
      num.overflow = false;
      break;

    default: /* case CPP_NOT: */
      num.low = num_zerop (num);
      num.high = 0;
      num.overflow = false;
      num.unsignedp = false;
      break;
    }

  return num;
}