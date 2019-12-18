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
struct macro_name_list {int dummy; } ;
struct macro_definition {char* replacement; int argc; char** argv; } ;
struct macro_buffer {scalar_t__ len; scalar_t__ last_token; char* text; scalar_t__ is_identifier; } ;
typedef  int /*<<< orphan*/  macro_lookup_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  append_tokens_without_splicing (struct macro_buffer*,struct macro_buffer*) ; 
 int /*<<< orphan*/  appendmem (struct macro_buffer*,char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  get_token (struct macro_buffer*,struct macro_buffer*) ; 
 int /*<<< orphan*/  init_shared_buffer (struct macro_buffer*,char*,int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  scan (struct macro_buffer*,struct macro_buffer*,struct macro_name_list*,int /*<<< orphan*/ *,void*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
substitute_args (struct macro_buffer *dest, 
                 struct macro_definition *def,
                 int argc, struct macro_buffer *argv,
                 struct macro_name_list *no_loop,
                 macro_lookup_ftype *lookup_func,
                 void *lookup_baton)
{
  /* A macro buffer for the macro's replacement list.  */
  struct macro_buffer replacement_list;

  init_shared_buffer (&replacement_list, (char *) def->replacement,
                      strlen (def->replacement));

  gdb_assert (dest->len == 0);
  dest->last_token = 0;

  for (;;)
    {
      struct macro_buffer tok;
      char *original_rl_start = replacement_list.text;
      int substituted = 0;
      
      /* Find the next token in the replacement list.  */
      if (! get_token (&tok, &replacement_list))
        break;

      /* Just for aesthetics.  If we skipped some whitespace, copy
         that to DEST.  */
      if (tok.text > original_rl_start)
        {
          appendmem (dest, original_rl_start, tok.text - original_rl_start);
          dest->last_token = dest->len;
        }

      /* Is this token the stringification operator?  */
      if (tok.len == 1
          && tok.text[0] == '#')
        error ("Stringification is not implemented yet.");

      /* Is this token the splicing operator?  */
      if (tok.len == 2
          && tok.text[0] == '#'
          && tok.text[1] == '#')
        error ("Token splicing is not implemented yet.");

      /* Is this token an identifier?  */
      if (tok.is_identifier)
        {
          int i;

          /* Is it the magic varargs parameter?  */
          if (tok.len == 11
              && ! memcmp (tok.text, "__VA_ARGS__", 11))
            error ("Variable-arity macros not implemented yet.");

          /* Is it one of the parameters?  */
          for (i = 0; i < def->argc; i++)
            if (tok.len == strlen (def->argv[i])
                && ! memcmp (tok.text, def->argv[i], tok.len))
              {
                struct macro_buffer arg_src;

                /* Expand any macro invocations in the argument text,
                   and append the result to dest.  Remember that scan
                   mutates its source, so we need to scan a new buffer
                   referring to the argument's text, not the argument
                   itself.  */
                init_shared_buffer (&arg_src, argv[i].text, argv[i].len);
                scan (dest, &arg_src, no_loop, lookup_func, lookup_baton);
                substituted = 1;
                break;
              }
        }

      /* If it wasn't a parameter, then just copy it across.  */
      if (! substituted)
        append_tokens_without_splicing (dest, &tok);
    }
}