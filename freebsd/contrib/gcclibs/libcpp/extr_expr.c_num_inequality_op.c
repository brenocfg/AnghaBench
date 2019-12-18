#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_9__ {int low; int overflow; int unsignedp; scalar_t__ high; } ;
typedef  TYPE_1__ cpp_num ;

/* Variables and functions */
 int CPP_GREATER ; 
 int CPP_GREATER_EQ ; 
 int CPP_LESS ; 
 int /*<<< orphan*/  CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ num_eq (TYPE_1__,TYPE_1__) ; 
 int num_greater_eq (TYPE_1__,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  precision ; 

__attribute__((used)) static cpp_num
num_inequality_op (cpp_reader *pfile, cpp_num lhs, cpp_num rhs,
		   enum cpp_ttype op)
{
  bool gte = num_greater_eq (lhs, rhs, CPP_OPTION (pfile, precision));

  if (op == CPP_GREATER_EQ)
    lhs.low = gte;
  else if (op == CPP_LESS)
    lhs.low = !gte;
  else if (op == CPP_GREATER)
    lhs.low = gte && !num_eq (lhs, rhs);
  else /* CPP_LESS_EQ.  */
    lhs.low = !gte || num_eq (lhs, rhs);

  lhs.high = 0;
  lhs.overflow = false;
  lhs.unsignedp = false;
  return lhs;
}