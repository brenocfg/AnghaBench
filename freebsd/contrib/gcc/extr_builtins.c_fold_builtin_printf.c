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
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;

/* Variables and functions */
 int BUILT_IN_PRINTF_CHK ; 
 int BUILT_IN_PRINTF_UNLOCKED ; 
 size_t BUILT_IN_PUTCHAR ; 
 size_t BUILT_IN_PUTCHAR_UNLOCKED ; 
 size_t BUILT_IN_PUTS ; 
 size_t BUILT_IN_PUTS_UNLOCKED ; 
 int BUILT_IN_VPRINTF ; 
 int BUILT_IN_VPRINTF_CHK ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_SIDE_EFFECTS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 char* alloca (size_t) ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,char const) ; 
 scalar_t__ build_string_literal (size_t,char*) ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 scalar_t__* built_in_decls ; 
 char* c_getstr (scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__* implicit_built_in_decls ; 
 int /*<<< orphan*/  init_target_chars () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/ * strchr (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 unsigned char target_newline ; 
 int /*<<< orphan*/  target_percent ; 
 int /*<<< orphan*/  target_percent_c ; 
 int /*<<< orphan*/  target_percent_s ; 
 int /*<<< orphan*/  target_percent_s_newline ; 

__attribute__((used)) static tree
fold_builtin_printf (tree fndecl, tree arglist, bool ignore,
		     enum built_in_function fcode)
{
  tree fmt, fn = NULL_TREE, fn_putchar, fn_puts, arg, call;
  const char *fmt_str = NULL;

  /* If the return value is used, don't do the transformation.  */
  if (! ignore)
    return 0;

  /* Verify the required arguments in the original call.  */
  if (fcode == BUILT_IN_PRINTF_CHK || fcode == BUILT_IN_VPRINTF_CHK)
    {
      tree flag;

      if (! arglist)
	return 0;
      flag = TREE_VALUE (arglist);
      if (TREE_CODE (TREE_TYPE (flag)) != INTEGER_TYPE
	  || TREE_SIDE_EFFECTS (flag))
	return 0;
      arglist = TREE_CHAIN (arglist);
    }

  if (! arglist)
    return 0;
  fmt = TREE_VALUE (arglist);
  if (! POINTER_TYPE_P (TREE_TYPE (fmt)))
    return 0;
  arglist = TREE_CHAIN (arglist);

  /* Check whether the format is a literal string constant.  */
  fmt_str = c_getstr (fmt);
  if (fmt_str == NULL)
    return NULL_TREE;

  if (fcode == BUILT_IN_PRINTF_UNLOCKED)
    {
      /* If we're using an unlocked function, assume the other
	 unlocked functions exist explicitly.  */
      fn_putchar = built_in_decls[BUILT_IN_PUTCHAR_UNLOCKED];
      fn_puts = built_in_decls[BUILT_IN_PUTS_UNLOCKED];
    }
  else
    {
      fn_putchar = implicit_built_in_decls[BUILT_IN_PUTCHAR];
      fn_puts = implicit_built_in_decls[BUILT_IN_PUTS];
    }

  if (!init_target_chars())
    return 0;

  if (strcmp (fmt_str, target_percent_s) == 0 || strchr (fmt_str, target_percent) == NULL)
    {
      const char *str;

      if (strcmp (fmt_str, target_percent_s) == 0)
	{
	  if (fcode == BUILT_IN_VPRINTF || fcode == BUILT_IN_VPRINTF_CHK)
	    return 0;

	  if (! arglist
	      || ! POINTER_TYPE_P (TREE_TYPE (TREE_VALUE (arglist)))
	      || TREE_CHAIN (arglist))
	    return 0;

	  str = c_getstr (TREE_VALUE (arglist));
	  if (str == NULL)
	    return 0;
	}
      else
	{
	  /* The format specifier doesn't contain any '%' characters.  */
	  if (fcode != BUILT_IN_VPRINTF && fcode != BUILT_IN_VPRINTF_CHK
	      && arglist)
	    return 0;
	  str = fmt_str;
	}

      /* If the string was "", printf does nothing.  */
      if (str[0] == '\0')
	return build_int_cst (TREE_TYPE (TREE_TYPE (fndecl)), 0);

      /* If the string has length of 1, call putchar.  */
      if (str[1] == '\0')
	{
	  /* Given printf("c"), (where c is any one character,)
	     convert "c"[0] to an int and pass that to the replacement
	     function.  */
	  arg = build_int_cst (NULL_TREE, str[0]);
	  arglist = build_tree_list (NULL_TREE, arg);
	  fn = fn_putchar;
	}
      else
	{
	  /* If the string was "string\n", call puts("string").  */
	  size_t len = strlen (str);
	  if ((unsigned char)str[len - 1] == target_newline)
	    {
	      /* Create a NUL-terminated string that's one char shorter
		 than the original, stripping off the trailing '\n'.  */
	      char *newstr = alloca (len);
	      memcpy (newstr, str, len - 1);
	      newstr[len - 1] = 0;

	      arg = build_string_literal (len, newstr);
	      arglist = build_tree_list (NULL_TREE, arg);
	      fn = fn_puts;
	    }
	  else
	    /* We'd like to arrange to call fputs(string,stdout) here,
	       but we need stdout and don't have a way to get it yet.  */
	    return 0;
	}
    }

  /* The other optimizations can be done only on the non-va_list variants.  */
  else if (fcode == BUILT_IN_VPRINTF || fcode == BUILT_IN_VPRINTF_CHK)
    return 0;

  /* If the format specifier was "%s\n", call __builtin_puts(arg).  */
  else if (strcmp (fmt_str, target_percent_s_newline) == 0)
    {
      if (! arglist
	  || ! POINTER_TYPE_P (TREE_TYPE (TREE_VALUE (arglist)))
	  || TREE_CHAIN (arglist))
	return 0;
      fn = fn_puts;
    }

  /* If the format specifier was "%c", call __builtin_putchar(arg).  */
  else if (strcmp (fmt_str, target_percent_c) == 0)
    {
      if (! arglist
	  || TREE_CODE (TREE_TYPE (TREE_VALUE (arglist))) != INTEGER_TYPE
	  || TREE_CHAIN (arglist))
	return 0;
      fn = fn_putchar;
    }

  if (!fn)
    return 0;

  call = build_function_call_expr (fn, arglist);
  return fold_convert (TREE_TYPE (TREE_TYPE (fndecl)), call);
}