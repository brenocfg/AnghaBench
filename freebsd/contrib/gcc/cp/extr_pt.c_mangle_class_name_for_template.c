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
struct obstack {int dummy; } ;

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ INNERMOST_TEMPLATE_ARGS (scalar_t__) ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TEMPLATE_DECL ; 
 int /*<<< orphan*/  TFF_CHASE_TYPEDEF ; 
 int /*<<< orphan*/  TFF_PLAIN_IDENTIFIER ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  cat (char const*) ; 
 int /*<<< orphan*/  ccat (char) ; 
 char* decl_as_string (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 char* expr_as_string (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_obstack_init (struct obstack*) ; 
 scalar_t__ obstack_alloc (struct obstack*,int) ; 
 scalar_t__ obstack_base (struct obstack*) ; 
 int /*<<< orphan*/  obstack_blank_fast (struct obstack*,int) ; 
 int /*<<< orphan*/  obstack_free (struct obstack*,char*) ; 
 char* obstack_next_free (struct obstack*) ; 
 char* type_as_string (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
mangle_class_name_for_template (const char* name, tree parms, tree arglist)
{
  static struct obstack scratch_obstack;
  static char *scratch_firstobj;
  int i, nparms;

  if (!scratch_firstobj)
    gcc_obstack_init (&scratch_obstack);
  else
    obstack_free (&scratch_obstack, scratch_firstobj);
  scratch_firstobj = (char *) obstack_alloc (&scratch_obstack, 1);

#define ccat(C)	obstack_1grow (&scratch_obstack, (C));
#define cat(S)	obstack_grow (&scratch_obstack, (S), strlen (S))

  cat (name);
  ccat ('<');
  nparms = TREE_VEC_LENGTH (parms);
  arglist = INNERMOST_TEMPLATE_ARGS (arglist);
  gcc_assert (nparms == TREE_VEC_LENGTH (arglist));
  for (i = 0; i < nparms; i++)
    {
      tree parm;
      tree arg;

      parm = TREE_VALUE (TREE_VEC_ELT (parms, i));
      arg = TREE_VEC_ELT (arglist, i);

      if (parm == error_mark_node)
	continue;

      if (i)
	ccat (',');

      if (TREE_CODE (parm) == TYPE_DECL)
	{
	  cat (type_as_string (arg, TFF_CHASE_TYPEDEF));
	  continue;
	}
      else if (TREE_CODE (parm) == TEMPLATE_DECL)
	{
	  if (TREE_CODE (arg) == TEMPLATE_DECL)
	    {
	      /* Already substituted with real template.  Just output
		 the template name here */
	      tree context = DECL_CONTEXT (arg);
	      if (context)
		{
		  /* The template may be defined in a namespace, or
		     may be a member template.  */
		  gcc_assert (TREE_CODE (context) == NAMESPACE_DECL
			      || CLASS_TYPE_P (context));
		  cat (decl_as_string (DECL_CONTEXT (arg),
				      TFF_PLAIN_IDENTIFIER));
		  cat ("::");
		}
	      cat (IDENTIFIER_POINTER (DECL_NAME (arg)));
	    }
	  else
	    /* Output the parameter declaration.  */
	    cat (type_as_string (arg, TFF_CHASE_TYPEDEF));
	  continue;
	}
      else
	gcc_assert (TREE_CODE (parm) == PARM_DECL);

      /* No need to check arglist against parmlist here; we did that
	 in coerce_template_parms, called from lookup_template_class.  */
      cat (expr_as_string (arg, TFF_PLAIN_IDENTIFIER));
    }
  {
    char *bufp = obstack_next_free (&scratch_obstack);
    int offset = 0;
    while (bufp[offset - 1] == ' ')
      offset--;
    obstack_blank_fast (&scratch_obstack, offset);

    /* B<C<char> >, not B<C<char>> */
    if (bufp[offset - 1] == '>')
      ccat (' ');
  }
  ccat ('>');
  ccat ('\0');
  return (char *) obstack_base (&scratch_obstack);
}