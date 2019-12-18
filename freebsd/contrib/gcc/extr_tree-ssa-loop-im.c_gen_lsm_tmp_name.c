#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
#define  ALIGN_INDIRECT_REF 142 
#define  ARRAY_RANGE_REF 141 
#define  ARRAY_REF 140 
#define  BIT_FIELD_REF 139 
#define  COMPONENT_REF 138 
#define  IMAGPART_EXPR 137 
#define  INDIRECT_REF 136 
#define  MISALIGNED_INDIRECT_REF 135 
#define  PARM_DECL 134 
#define  REALPART_EXPR 133 
#define  RESULT_DECL 132 
#define  SSA_NAME 131 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
#define  STRING_CST 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  VAR_DECL 129 
#define  VIEW_CONVERT_EXPR 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char* get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_tmp_name_add (char const*) ; 

__attribute__((used)) static void
gen_lsm_tmp_name (tree ref)
{
  const char *name;

  switch (TREE_CODE (ref))
    {
    case MISALIGNED_INDIRECT_REF:
    case ALIGN_INDIRECT_REF:
    case INDIRECT_REF:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_");
      break;

    case BIT_FIELD_REF:
    case VIEW_CONVERT_EXPR:
    case ARRAY_RANGE_REF:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      break;

    case REALPART_EXPR:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_RE");
      break;
      
    case IMAGPART_EXPR:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_IM");
      break;

    case COMPONENT_REF:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_");
      name = get_name (TREE_OPERAND (ref, 1));
      if (!name)
	name = "F";
      lsm_tmp_name_add ("_");
      lsm_tmp_name_add (name);

    case ARRAY_REF:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_I");
      break;

    case SSA_NAME:
      ref = SSA_NAME_VAR (ref);
      /* Fallthru.  */

    case VAR_DECL:
    case PARM_DECL:
      name = get_name (ref);
      if (!name)
	name = "D";
      lsm_tmp_name_add (name);
      break;

    case STRING_CST:
      lsm_tmp_name_add ("S");
      break;

    case RESULT_DECL:
      lsm_tmp_name_add ("R");
      break;

    default:
      gcc_unreachable ();
    }
}