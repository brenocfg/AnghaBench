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

/* Variables and functions */
 unsigned int BITS_PER_WORD ; 
 scalar_t__ COMPLETE_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (scalar_t__) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 unsigned int PARM_BOUNDARY ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 unsigned int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (scalar_t__) ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_identifier_with_length (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ tree_last (scalar_t__) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static tree
gen_regparm_prefix (tree decl, unsigned nregs)
{
  unsigned total = 0;
  /* ??? This probably should use XSTR (XEXP (DECL_RTL (decl), 0), 0) instead
     of DECL_ASSEMBLER_NAME.  */
  const char *asmname = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl));
  char *newsym;
  tree formal_type = TYPE_ARG_TYPES (TREE_TYPE (decl));

  if (formal_type != NULL_TREE)
    {
      /* This attribute is ignored for variadic functions.  */ 
      if (TREE_VALUE (tree_last (formal_type)) != void_type_node)
	return NULL_TREE;

      /* Quit if we hit an incomplete type.  Error is reported
	 by convert_arguments in c-typeck.c or cp/typeck.c.  */
      while (TREE_VALUE (formal_type) != void_type_node
	     && COMPLETE_TYPE_P (TREE_VALUE (formal_type)))	
	{
	  unsigned parm_size
	    = TREE_INT_CST_LOW (TYPE_SIZE (TREE_VALUE (formal_type)));

	  /* Must round up to include padding.  This is done the same
	     way as in store_one_arg.  */
	  parm_size = ((parm_size + PARM_BOUNDARY - 1)
		       / PARM_BOUNDARY * PARM_BOUNDARY);
	  total += parm_size;
	  formal_type = TREE_CHAIN (formal_type);
	}
    }

  if (nregs > total / BITS_PER_WORD)
    nregs = total / BITS_PER_WORD;
  gcc_assert (nregs <= 9);
  newsym = alloca (3 + strlen (asmname) + 1);
  return get_identifier_with_length (newsym,
				     sprintf (newsym,
					      "_%u@%s",
					      nregs,
					      asmname));
}