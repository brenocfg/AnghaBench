#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_6__ {int need_abi_warning; } ;
struct TYPE_5__ {scalar_t__ identifier; char* mangled_name; } ;
struct TYPE_4__ {scalar_t__ identifier; int arity; char* mangled_name; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 int BASELINK ; 
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 int BOUND_TEMPLATE_TEMPLATE_PARM ; 
#define  CALL_EXPR 132 
#define  CAST_EXPR 131 
 int COND_EXPR ; 
#define  CONST_CAST_EXPR 130 
 int CONST_DECL ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 TYPE_3__ G ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ IDENTIFIER_OPNAME_P (scalar_t__) ; 
 scalar_t__ IDENTIFIER_TYPENAME_P (scalar_t__) ; 
 int LAST_CPLUS_TREE_CODE ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int PTRMEM_CST ; 
 int /*<<< orphan*/  PTRMEM_CST_CLASS (scalar_t__) ; 
 int /*<<< orphan*/  PTRMEM_CST_MEMBER (scalar_t__) ; 
 scalar_t__ REFERENCE_TYPE ; 
#define  SCOPE_REF 129 
 scalar_t__ SIZEOF_EXPR ; 
#define  STATIC_CAST_EXPR 128 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 int TEMPLATE_PARM_INDEX ; 
 int TEMPLATE_TEMPLATE_PARM ; 
 int TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int TREE_CODE_LENGTH (int) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ abi_version_at_least (int) ; 
 TYPE_2__* assignment_operator_name_info ; 
 scalar_t__ build_nt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_qualified_name (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* operator_name_info ; 
 int /*<<< orphan*/  sorry (char*) ; 
 scalar_t__ tcc_constant ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_conversion_operator_name (scalar_t__) ; 
 int /*<<< orphan*/  write_encoding (scalar_t__) ; 
 int /*<<< orphan*/  write_mangled_name (scalar_t__,int) ; 
 int /*<<< orphan*/  write_source_name (scalar_t__) ; 
 int /*<<< orphan*/  write_string (char const*) ; 
 int /*<<< orphan*/  write_template_arg_literal (scalar_t__) ; 
 int /*<<< orphan*/  write_template_args (scalar_t__) ; 
 int /*<<< orphan*/  write_template_param (scalar_t__) ; 
 int /*<<< orphan*/  write_type (scalar_t__) ; 

__attribute__((used)) static void
write_expression (tree expr)
{
  enum tree_code code;

  code = TREE_CODE (expr);

  /* Skip NOP_EXPRs.  They can occur when (say) a pointer argument
     is converted (via qualification conversions) to another
     type.  */
  while (TREE_CODE (expr) == NOP_EXPR
	 || TREE_CODE (expr) == NON_LVALUE_EXPR)
    {
      expr = TREE_OPERAND (expr, 0);
      code = TREE_CODE (expr);
    }

  if (code == BASELINK)
    {
      expr = BASELINK_FUNCTIONS (expr);
      code = TREE_CODE (expr);
    }

  /* Handle pointers-to-members by making them look like expression
     nodes.  */
  if (code == PTRMEM_CST)
    {
      expr = build_nt (ADDR_EXPR,
		       build_qualified_name (/*type=*/NULL_TREE,
					     PTRMEM_CST_CLASS (expr),
					     PTRMEM_CST_MEMBER (expr),
					     /*template_p=*/false));
      code = TREE_CODE (expr);
    }

  /* Handle template parameters.  */
  if (code == TEMPLATE_TYPE_PARM
      || code == TEMPLATE_TEMPLATE_PARM
      || code == BOUND_TEMPLATE_TEMPLATE_PARM
      || code == TEMPLATE_PARM_INDEX)
    write_template_param (expr);
  /* Handle literals.  */
  else if (TREE_CODE_CLASS (code) == tcc_constant
	   || (abi_version_at_least (2) && code == CONST_DECL))
    write_template_arg_literal (expr);
  else if (DECL_P (expr))
    {
      /* G++ 3.2 incorrectly mangled non-type template arguments of
	 enumeration type using their names.  */
      if (code == CONST_DECL)
	G.need_abi_warning = 1;
      write_char ('L');
      write_mangled_name (expr, false);
      write_char ('E');
    }
  else if (TREE_CODE (expr) == SIZEOF_EXPR
	   && TYPE_P (TREE_OPERAND (expr, 0)))
    {
      write_string ("st");
      write_type (TREE_OPERAND (expr, 0));
    }
  else if (abi_version_at_least (2) && TREE_CODE (expr) == SCOPE_REF)
    {
      tree scope = TREE_OPERAND (expr, 0);
      tree member = TREE_OPERAND (expr, 1);

      /* If the MEMBER is a real declaration, then the qualifying
	 scope was not dependent.  Ideally, we would not have a
	 SCOPE_REF in those cases, but sometimes we do.  If the second
	 argument is a DECL, then the name must not have been
	 dependent.  */
      if (DECL_P (member))
	write_expression (member);
      else
	{
	  tree template_args;

	  write_string ("sr");
	  write_type (scope);
	  /* If MEMBER is a template-id, separate the template
	     from the arguments.  */
	  if (TREE_CODE (member) == TEMPLATE_ID_EXPR)
	    {
	      template_args = TREE_OPERAND (member, 1);
	      member = TREE_OPERAND (member, 0);
	    }
	  else
	    template_args = NULL_TREE;
	  /* Write out the name of the MEMBER.  */
	  if (IDENTIFIER_TYPENAME_P (member))
	    write_conversion_operator_name (TREE_TYPE (member));
	  else if (IDENTIFIER_OPNAME_P (member))
	    {
	      int i;
	      const char *mangled_name = NULL;

	      /* Unfortunately, there is no easy way to go from the
		 name of the operator back to the corresponding tree
		 code.  */
	      for (i = 0; i < LAST_CPLUS_TREE_CODE; ++i)
		if (operator_name_info[i].identifier == member)
		  {
		    /* The ABI says that we prefer binary operator
		       names to unary operator names.  */
		    if (operator_name_info[i].arity == 2)
		      {
			mangled_name = operator_name_info[i].mangled_name;
			break;
		      }
		    else if (!mangled_name)
		      mangled_name = operator_name_info[i].mangled_name;
		  }
		else if (assignment_operator_name_info[i].identifier
			 == member)
		  {
		    mangled_name
		      = assignment_operator_name_info[i].mangled_name;
		    break;
		  }
	      write_string (mangled_name);
	    }
	  else
	    write_source_name (member);
	  /* Write out the template arguments.  */
	  if (template_args)
	    write_template_args (template_args);
	}
    }
  else
    {
      int i;

      /* When we bind a variable or function to a non-type template
	 argument with reference type, we create an ADDR_EXPR to show
	 the fact that the entity's address has been taken.  But, we
	 don't actually want to output a mangling code for the `&'.  */
      if (TREE_CODE (expr) == ADDR_EXPR
	  && TREE_TYPE (expr)
	  && TREE_CODE (TREE_TYPE (expr)) == REFERENCE_TYPE)
	{
	  expr = TREE_OPERAND (expr, 0);
	  if (DECL_P (expr))
	    {
	      write_expression (expr);
	      return;
	    }

	  code = TREE_CODE (expr);
	}

      /* If it wasn't any of those, recursively expand the expression.  */
      write_string (operator_name_info[(int) code].mangled_name);

      switch (code)
	{
	case CALL_EXPR:
	  sorry ("call_expr cannot be mangled due to a defect in the C++ ABI");
	  break;

	case CAST_EXPR:
	  write_type (TREE_TYPE (expr));
	  /* There is no way to mangle a zero-operand cast like
	     "T()".  */
	  if (!TREE_OPERAND (expr, 0))
	    sorry ("zero-operand casts cannot be mangled due to a defect "
		   "in the C++ ABI");
	  else
	    write_expression (TREE_VALUE (TREE_OPERAND (expr, 0)));
	  break;

	case STATIC_CAST_EXPR:
	case CONST_CAST_EXPR:
	  write_type (TREE_TYPE (expr));
	  write_expression (TREE_OPERAND (expr, 0));
	  break;


	/* Handle pointers-to-members specially.  */
	case SCOPE_REF:
	  write_type (TREE_OPERAND (expr, 0));
	  if (TREE_CODE (TREE_OPERAND (expr, 1)) == IDENTIFIER_NODE)
	    write_source_name (TREE_OPERAND (expr, 1));
	  else if (TREE_CODE (TREE_OPERAND (expr, 1)) == TEMPLATE_ID_EXPR)
	    {
	      tree template_id;
	      tree name;

	      template_id = TREE_OPERAND (expr, 1);
	      name = TREE_OPERAND (template_id, 0);
	      /* FIXME: What about operators?  */
	      gcc_assert (TREE_CODE (name) == IDENTIFIER_NODE);
	      write_source_name (TREE_OPERAND (template_id, 0));
	      write_template_args (TREE_OPERAND (template_id, 1));
	    }
	  else
	    {
	      /* G++ 3.2 incorrectly put out both the "sr" code and
		 the nested name of the qualified name.  */
	      G.need_abi_warning = 1;
	      write_encoding (TREE_OPERAND (expr, 1));
	    }
	  break;

	default:
	  for (i = 0; i < TREE_CODE_LENGTH (code); ++i)
	    {
	      tree operand = TREE_OPERAND (expr, i);
	      /* As a GNU extension, the middle operand of a
		 conditional may be omitted.  Since expression
		 manglings are supposed to represent the input token
		 stream, there's no good way to mangle such an
		 expression without extending the C++ ABI.  */
	      if (code == COND_EXPR && i == 1 && !operand)
		{
		  error ("omitted middle operand to %<?:%> operand "
			 "cannot be mangled");
		  continue;
		}
	      write_expression (operand);
	    }
	}
    }
}