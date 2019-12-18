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
struct macro_buffer {char* text; scalar_t__ last_token; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  macro_lookup_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  appendc (struct macro_buffer*,char) ; 
 int /*<<< orphan*/  cleanup_macro_buffer ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  get_token (struct macro_buffer*,struct macro_buffer*) ; 
 int /*<<< orphan*/  init_buffer (struct macro_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_shared_buffer (struct macro_buffer*,char*,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct macro_buffer*) ; 
 scalar_t__ maybe_expand (struct macro_buffer*,struct macro_buffer*,struct macro_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

char *
macro_expand_next (char **lexptr,
                   macro_lookup_ftype *lookup_func,
                   void *lookup_baton)
{
  struct macro_buffer src, dest, tok;
  struct cleanup *back_to;

  /* Set up SRC to refer to the input text, pointed to by *lexptr.  */
  init_shared_buffer (&src, *lexptr, strlen (*lexptr));

  /* Set up DEST to receive the expansion, if there is one.  */
  init_buffer (&dest, 0);
  dest.last_token = 0;
  back_to = make_cleanup (cleanup_macro_buffer, &dest);

  /* Get the text's first preprocessing token.  */
  if (! get_token (&tok, &src))
    {
      do_cleanups (back_to);
      return 0;
    }

  /* If it's a macro invocation, expand it.  */
  if (maybe_expand (&dest, &tok, &src, 0, lookup_func, lookup_baton))
    {
      /* It was a macro invocation!  Package up the expansion as a
         null-terminated string and return it.  Set *lexptr to the
         start of the next token in the input.  */
      appendc (&dest, '\0');
      discard_cleanups (back_to);
      *lexptr = src.text;
      return dest.text;
    }
  else
    {
      /* It wasn't a macro invocation.  */
      do_cleanups (back_to);
      return 0;
    }
}