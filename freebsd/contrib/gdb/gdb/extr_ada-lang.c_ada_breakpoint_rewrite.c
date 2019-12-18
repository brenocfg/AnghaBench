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

/* Variables and functions */

char *
ada_breakpoint_rewrite (char *arg, int *break_on_exceptionp)
{
  if (arg == NULL)
    return arg;
  *break_on_exceptionp = 0;
  /* FIXME: language_ada should be defined in defs.h */
  /*  if (current_language->la_language == language_ada
     && DEPRECATED_STREQN (arg, "exception", 9) &&
     (arg[9] == ' ' || arg[9] == '\t' || arg[9] == '\0'))
     {
     char *tok, *end_tok;
     int toklen;

     *break_on_exceptionp = 1;

     tok = arg+9;
     while (*tok == ' ' || *tok == '\t')
     tok += 1;

     end_tok = tok;

     while (*end_tok != ' ' && *end_tok != '\t' && *end_tok != '\000')
     end_tok += 1;

     toklen = end_tok - tok;

     arg = (char*) xmalloc (sizeof ("__gnat_raise_nodefer_with_msg if "
     "long_integer(e) = long_integer(&)")
     + toklen + 1);
     make_cleanup (xfree, arg);
     if (toklen == 0)
     strcpy (arg, "__gnat_raise_nodefer_with_msg");
     else if (DEPRECATED_STREQN (tok, "unhandled", toklen))
     {
     *break_on_exceptionp = 2;
     strcpy (arg, "__gnat_unhandled_exception");
     }
     else
     {
     sprintf (arg, "__gnat_raise_nodefer_with_msg if "
     "long_integer(e) = long_integer(&%.*s)", 
     toklen, tok);
     }
     }
     else if (current_language->la_language == language_ada
     && DEPRECATED_STREQN (arg, "assert", 6) &&
     (arg[6] == ' ' || arg[6] == '\t' || arg[6] == '\0'))
     {
     char *tok = arg + 6;

     *break_on_exceptionp = 3;

     arg = (char*) 
     xmalloc (sizeof ("system__assertions__raise_assert_failure")
     + strlen (tok) + 1);
     make_cleanup (xfree, arg);
     sprintf (arg, "system__assertions__raise_assert_failure%s", tok);
     }
   */
  return arg;
}