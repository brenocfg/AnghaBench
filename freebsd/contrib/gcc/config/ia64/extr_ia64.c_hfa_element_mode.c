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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  ARRAY_TYPE 143 
#define  BOOLEAN_TYPE 142 
#define  COMPLEX_TYPE 141 
#define  ENUMERAL_TYPE 140 
 int FIELD_DECL ; 
#define  FUNCTION_TYPE 139 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 int GET_MODE_INNER (int) ; 
#define  INTEGER_TYPE 138 
#define  LANG_TYPE 137 
#define  METHOD_TYPE 136 
 int /*<<< orphan*/  MODE_COMPLEX_FLOAT ; 
 int /*<<< orphan*/  MODE_FLOAT ; 
#define  OFFSET_TYPE 135 
#define  POINTER_TYPE 134 
#define  QUAL_UNION_TYPE 133 
#define  REAL_TYPE 132 
#define  RECORD_TYPE 131 
#define  REFERENCE_TYPE 130 
 int TCmode ; 
 int TFmode ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 129 
#define  VOID_TYPE 128 
 int VOIDmode ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum machine_mode
hfa_element_mode (tree type, bool nested)
{
  enum machine_mode element_mode = VOIDmode;
  enum machine_mode mode;
  enum tree_code code = TREE_CODE (type);
  int know_element_mode = 0;
  tree t;

  if (!nested && (!TYPE_SIZE (type) || integer_zerop (TYPE_SIZE (type))))
    return VOIDmode;

  switch (code)
    {
    case VOID_TYPE:	case INTEGER_TYPE:	case ENUMERAL_TYPE:
    case BOOLEAN_TYPE:	case POINTER_TYPE:
    case OFFSET_TYPE:	case REFERENCE_TYPE:	case METHOD_TYPE:
    case LANG_TYPE:		case FUNCTION_TYPE:
      return VOIDmode;

      /* Fortran complex types are supposed to be HFAs, so we need to handle
	 gcc's COMPLEX_TYPEs as HFAs.  We need to exclude the integral complex
	 types though.  */
    case COMPLEX_TYPE:
      if (GET_MODE_CLASS (TYPE_MODE (type)) == MODE_COMPLEX_FLOAT
	  && TYPE_MODE (type) != TCmode)
	return GET_MODE_INNER (TYPE_MODE (type));
      else
	return VOIDmode;

    case REAL_TYPE:
      /* We want to return VOIDmode for raw REAL_TYPEs, but the actual
	 mode if this is contained within an aggregate.  */
      if (nested && TYPE_MODE (type) != TFmode)
	return TYPE_MODE (type);
      else
	return VOIDmode;

    case ARRAY_TYPE:
      return hfa_element_mode (TREE_TYPE (type), 1);

    case RECORD_TYPE:
    case UNION_TYPE:
    case QUAL_UNION_TYPE:
      for (t = TYPE_FIELDS (type); t; t = TREE_CHAIN (t))
	{
	  if (TREE_CODE (t) != FIELD_DECL)
	    continue;

	  mode = hfa_element_mode (TREE_TYPE (t), 1);
	  if (know_element_mode)
	    {
	      if (mode != element_mode)
		return VOIDmode;
	    }
	  else if (GET_MODE_CLASS (mode) != MODE_FLOAT)
	    return VOIDmode;
	  else
	    {
	      know_element_mode = 1;
	      element_mode = mode;
	    }
	}
      return element_mode;

    default:
      /* If we reach here, we probably have some front-end specific type
	 that the backend doesn't know about.  This can happen via the
	 aggregate_value_p call in init_function_start.  All we can do is
	 ignore unknown tree types.  */
      return VOIDmode;
    }

  return VOIDmode;
}