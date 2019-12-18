#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* dfp_binary_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ;
typedef  int /*<<< orphan*/  decNumber ;
struct TYPE_6__ {int /*<<< orphan*/  round; } ;
typedef  TYPE_1__ decContext ;
typedef  int /*<<< orphan*/  IEEE_TYPE ;
typedef  int /*<<< orphan*/  DFP_C_TYPE ;

/* Variables and functions */
 scalar_t__ CONTEXT_ERRORS (TYPE_1__) ; 
 int /*<<< orphan*/  CONTEXT_INIT ; 
 int /*<<< orphan*/  CONTEXT_ROUND ; 
 scalar_t__ CONTEXT_TRAPS ; 
 int /*<<< orphan*/  DFP_RAISE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_TO_IEEE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TO_INTERNAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decContextDefault (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ decNumberIsNegative (int /*<<< orphan*/ *) ; 
 scalar_t__ decNumberIsZero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
dfp_compare_op (dfp_binary_func op, DFP_C_TYPE arg_a, DFP_C_TYPE arg_b)
{
  IEEE_TYPE a, b;
  decContext context;
  decNumber arg1, arg2, res;
  int result;

  HOST_TO_IEEE (arg_a, &a);
  HOST_TO_IEEE (arg_b, &b);

  decContextDefault (&context, CONTEXT_INIT);
  context.round = CONTEXT_ROUND;

  TO_INTERNAL (&a, &arg1);
  TO_INTERNAL (&b, &arg2);

  /* Perform the comparison.  */
  op (&res, &arg1, &arg2, &context);

  if (CONTEXT_TRAPS && CONTEXT_ERRORS (context))
    DFP_RAISE (0);

  if (decNumberIsNegative (&res))
    result = -1;
  else if (decNumberIsZero (&res))
    result = 0;
  else
    result = 1;

  return result;
}