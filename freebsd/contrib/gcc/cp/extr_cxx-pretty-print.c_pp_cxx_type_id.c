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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  pp_flags ;
typedef  int /*<<< orphan*/  cxx_pretty_printer ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
#define  BOUND_TEMPLATE_TEMPLATE_PARM 140 
#define  ENUMERAL_TYPE 139 
#define  RECORD_TYPE 138 
#define  TEMPLATE_DECL 137 
#define  TEMPLATE_ID_EXPR 136 
#define  TEMPLATE_PARM_INDEX 135 
#define  TEMPLATE_TEMPLATE_PARM 134 
#define  TEMPLATE_TYPE_PARM 133 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TYPENAME_TYPE 132 
#define  TYPEOF_TYPE 131 
#define  TYPE_DECL 130 
#define  UNBOUND_CLASS_TEMPLATE 129 
#define  UNION_TYPE 128 
 TYPE_1__* pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_flag_abstract ; 
 int /*<<< orphan*/  pp_c_type_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_type_specifier_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_type_id (cxx_pretty_printer *pp, tree t)
{
  pp_flags saved_flags = pp_c_base (pp)->flags;
  pp_c_base (pp)->flags |= pp_c_flag_abstract;

  switch (TREE_CODE (t))
    {
    case TYPE_DECL:
    case UNION_TYPE:
    case RECORD_TYPE:
    case ENUMERAL_TYPE:
    case TYPENAME_TYPE:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
    case UNBOUND_CLASS_TEMPLATE:
    case TEMPLATE_TEMPLATE_PARM:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_PARM_INDEX:
    case TEMPLATE_DECL:
    case TYPEOF_TYPE:
    case TEMPLATE_ID_EXPR:
      pp_cxx_type_specifier_seq (pp, t);
      break;

    default:
      pp_c_type_id (pp_c_base (pp), t);
      break;
    }

  pp_c_base (pp)->flags = saved_flags;
}