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
 int BITS_PER_UNIT ; 
 scalar_t__ COMPLETE_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_ASSEMBLER_NAME (scalar_t__) ; 
 int /*<<< orphan*/  FASTCALL_PREFIX ; 
 char* IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int PARM_BOUNDARY ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (scalar_t__) ; 
 char* alloca (scalar_t__) ; 
 scalar_t__ get_identifier (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ tree_last (scalar_t__) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static tree
gen_stdcall_or_fastcall_suffix (tree decl, bool fastcall)
{
  int total = 0;
  /* ??? This probably should use XSTR (XEXP (DECL_RTL (decl), 0), 0) instead
     of DECL_ASSEMBLER_NAME.  */
   const char *asmname =  IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl));
  char *newsym;
  char *p;
  tree formal_type;

  /* Do not change the identifier if a verbatim asmspec or already done. */
  if (*asmname == '*' || strchr (asmname, '@'))
    return DECL_ASSEMBLER_NAME (decl);

  formal_type = TYPE_ARG_TYPES (TREE_TYPE (decl));
  if (formal_type != NULL_TREE)
    {
      /* These attributes are ignored for variadic functions in
	 i386.c:ix86_return_pops_args. For compatibility with MS
         compiler do not add @0 suffix here.  */ 
      if (TREE_VALUE (tree_last (formal_type)) != void_type_node)
        return DECL_ASSEMBLER_NAME (decl);

      /* Quit if we hit an incomplete type.  Error is reported
         by convert_arguments in c-typeck.c or cp/typeck.c.  */
      while (TREE_VALUE (formal_type) != void_type_node
	     && COMPLETE_TYPE_P (TREE_VALUE (formal_type)))	
	{
	  int parm_size
	    = TREE_INT_CST_LOW (TYPE_SIZE (TREE_VALUE (formal_type)));
	    /* Must round up to include padding.  This is done the same
	       way as in store_one_arg.  */
	  parm_size = ((parm_size + PARM_BOUNDARY - 1)
		       / PARM_BOUNDARY * PARM_BOUNDARY);
	  total += parm_size;
	  formal_type = TREE_CHAIN (formal_type);\
	}
     }

  /* Assume max of 8 base 10 digits in the suffix.  */
  newsym = alloca (1 + strlen (asmname) + 1 + 8 + 1);
  p = newsym;
  if (fastcall)
    *p++ = FASTCALL_PREFIX;
  sprintf (p, "%s@%d", asmname, total/BITS_PER_UNIT);
  return get_identifier (newsym);
}