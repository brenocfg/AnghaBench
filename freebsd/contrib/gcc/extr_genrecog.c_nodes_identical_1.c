#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  opno; int /*<<< orphan*/  intval; int /*<<< orphan*/  dup; int /*<<< orphan*/  veclen; int /*<<< orphan*/  c_test; TYPE_1__ pred; int /*<<< orphan*/  code; int /*<<< orphan*/  mode; int /*<<< orphan*/  num_insns; } ;
struct decision_test {int type; TYPE_2__ u; } ;

/* Variables and functions */
#define  DT_accept_insn 141 
#define  DT_accept_op 140 
#define  DT_c_test 139 
#define  DT_code 138 
#define  DT_dup 137 
#define  DT_elt_one_int 136 
#define  DT_elt_zero_int 135 
#define  DT_elt_zero_wide 134 
#define  DT_elt_zero_wide_safe 133 
#define  DT_mode 132 
#define  DT_num_insns 131 
#define  DT_pred 130 
#define  DT_veclen 129 
#define  DT_veclen_ge 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nodes_identical_1 (struct decision_test *d1, struct decision_test *d2)
{
  switch (d1->type)
    {
    case DT_num_insns:
      return d1->u.num_insns == d2->u.num_insns;

    case DT_mode:
      return d1->u.mode == d2->u.mode;

    case DT_code:
      return d1->u.code == d2->u.code;

    case DT_pred:
      return (d1->u.pred.mode == d2->u.pred.mode
	      && strcmp (d1->u.pred.name, d2->u.pred.name) == 0);

    case DT_c_test:
      return strcmp (d1->u.c_test, d2->u.c_test) == 0;

    case DT_veclen:
    case DT_veclen_ge:
      return d1->u.veclen == d2->u.veclen;

    case DT_dup:
      return d1->u.dup == d2->u.dup;

    case DT_elt_zero_int:
    case DT_elt_one_int:
    case DT_elt_zero_wide:
    case DT_elt_zero_wide_safe:
      return d1->u.intval == d2->u.intval;

    case DT_accept_op:
      return d1->u.opno == d2->u.opno;

    case DT_accept_insn:
      /* Differences will be handled in merge_accept_insn.  */
      return 1;

    default:
      gcc_unreachable ();
    }
}