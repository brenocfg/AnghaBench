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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  formals_style ;

/* Variables and functions */
#define  ARRAY_TYPE 139 
 int /*<<< orphan*/  COMPLETE_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
#define  ENUMERAL_TYPE 138 
#define  ERROR_MARK 137 
#define  FUNCTION_TYPE 136 
#define  IDENTIFIER_NODE 135 
 char const* IDENTIFIER_POINTER (scalar_t__) ; 
 int INTEGER_CST ; 
#define  INTEGER_TYPE 134 
#define  POINTER_TYPE 133 
#define  REAL_TYPE 132 
#define  RECORD_TYPE 131 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TYPE_DECL 130 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_QUALS (scalar_t__) ; 
 scalar_t__ TYPE_READONLY (scalar_t__) ; 
 scalar_t__ TYPE_RESTRICT (scalar_t__) ; 
 scalar_t__ TYPE_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ TYPE_VALUES (scalar_t__) ; 
 scalar_t__ TYPE_VOLATILE (scalar_t__) ; 
#define  UNION_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  ansi ; 
 char* concat (char const*,char const*,char*,...) ; 
 char const* data_type ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char const* gen_decl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* gen_formal_list_for_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int int_size_in_bytes (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static const char *
gen_type (const char *ret_val, tree t, formals_style style)
{
  tree chain_p;

  /* If there is a typedef name for this type, use it.  */
  if (TYPE_NAME (t) && TREE_CODE (TYPE_NAME (t)) == TYPE_DECL)
    data_type = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (t)));
  else
    {
      switch (TREE_CODE (t))
	{
	case POINTER_TYPE:
	  if (TYPE_READONLY (t))
	    ret_val = concat ("const ", ret_val, NULL);
	  if (TYPE_VOLATILE (t))
	    ret_val = concat ("volatile ", ret_val, NULL);

	  ret_val = concat ("*", ret_val, NULL);

	  if (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE || TREE_CODE (TREE_TYPE (t)) == FUNCTION_TYPE)
	    ret_val = concat ("(", ret_val, ")", NULL);

	  ret_val = gen_type (ret_val, TREE_TYPE (t), style);

	  return ret_val;

	case ARRAY_TYPE:
	  if (!COMPLETE_TYPE_P (t) || TREE_CODE (TYPE_SIZE (t)) != INTEGER_CST)
	    ret_val = gen_type (concat (ret_val, "[]", NULL),
				TREE_TYPE (t), style);
	  else if (int_size_in_bytes (t) == 0)
	    ret_val = gen_type (concat (ret_val, "[0]", NULL),
				TREE_TYPE (t), style);
	  else
	    {
	      int size = (int_size_in_bytes (t) / int_size_in_bytes (TREE_TYPE (t)));
	      char buff[10];
	      sprintf (buff, "[%d]", size);
	      ret_val = gen_type (concat (ret_val, buff, NULL),
				  TREE_TYPE (t), style);
	    }
	  break;

	case FUNCTION_TYPE:
	  ret_val = gen_type (concat (ret_val,
				      gen_formal_list_for_type (t, style),
				      NULL),
			      TREE_TYPE (t), style);
	  break;

	case IDENTIFIER_NODE:
	  data_type = IDENTIFIER_POINTER (t);
	  break;

	/* The following three cases are complicated by the fact that a
	   user may do something really stupid, like creating a brand new
	   "anonymous" type specification in a formal argument list (or as
	   part of a function return type specification).  For example:

		int f (enum { red, green, blue } color);

	   In such cases, we have no name that we can put into the prototype
	   to represent the (anonymous) type.  Thus, we have to generate the
	   whole darn type specification.  Yuck!  */

	case RECORD_TYPE:
	  if (TYPE_NAME (t))
	    data_type = IDENTIFIER_POINTER (TYPE_NAME (t));
	  else
	    {
	      data_type = "";
	      chain_p = TYPE_FIELDS (t);
	      while (chain_p)
		{
		  data_type = concat (data_type, gen_decl (chain_p, 0, ansi),
				      NULL);
		  chain_p = TREE_CHAIN (chain_p);
		  data_type = concat (data_type, "; ", NULL);
		}
	      data_type = concat ("{ ", data_type, "}", NULL);
	    }
	  data_type = concat ("struct ", data_type, NULL);
	  break;

	case UNION_TYPE:
	  if (TYPE_NAME (t))
	    data_type = IDENTIFIER_POINTER (TYPE_NAME (t));
	  else
	    {
	      data_type = "";
	      chain_p = TYPE_FIELDS (t);
	      while (chain_p)
		{
		  data_type = concat (data_type, gen_decl (chain_p, 0, ansi),
				      NULL);
		  chain_p = TREE_CHAIN (chain_p);
		  data_type = concat (data_type, "; ", NULL);
		}
	      data_type = concat ("{ ", data_type, "}", NULL);
	    }
	  data_type = concat ("union ", data_type, NULL);
	  break;

	case ENUMERAL_TYPE:
	  if (TYPE_NAME (t))
	    data_type = IDENTIFIER_POINTER (TYPE_NAME (t));
	  else
	    {
	      data_type = "";
	      chain_p = TYPE_VALUES (t);
	      while (chain_p)
		{
		  data_type = concat (data_type,
			IDENTIFIER_POINTER (TREE_PURPOSE (chain_p)), NULL);
		  chain_p = TREE_CHAIN (chain_p);
		  if (chain_p)
		    data_type = concat (data_type, ", ", NULL);
		}
	      data_type = concat ("{ ", data_type, " }", NULL);
	    }
	  data_type = concat ("enum ", data_type, NULL);
	  break;

	case TYPE_DECL:
	  data_type = IDENTIFIER_POINTER (DECL_NAME (t));
	  break;

	case INTEGER_TYPE:
	  data_type = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (t)));
	  /* Normally, `unsigned' is part of the deal.  Not so if it comes
	     with a type qualifier.  */
	  if (TYPE_UNSIGNED (t) && TYPE_QUALS (t))
	    data_type = concat ("unsigned ", data_type, NULL);
	  break;

	case REAL_TYPE:
	  data_type = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (t)));
	  break;

	case VOID_TYPE:
	  data_type = "void";
	  break;

	case ERROR_MARK:
	  data_type = "[ERROR]";
	  break;

	default:
	  gcc_unreachable ();
	}
    }
  if (TYPE_READONLY (t))
    ret_val = concat ("const ", ret_val, NULL);
  if (TYPE_VOLATILE (t))
    ret_val = concat ("volatile ", ret_val, NULL);
  if (TYPE_RESTRICT (t))
    ret_val = concat ("restrict ", ret_val, NULL);
  return ret_val;
}