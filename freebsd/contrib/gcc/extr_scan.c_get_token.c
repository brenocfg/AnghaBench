#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* ptr; scalar_t__* base; } ;
typedef  TYPE_1__ sstring ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CHAR_TOKEN ; 
 int EOF ; 
 int IDENTIFIER_TOKEN ; 
 int INT_TOKEN ; 
 scalar_t__ ISDIGIT (int) ; 
 scalar_t__ ISIDST (int) ; 
 int /*<<< orphan*/  MAKE_SSTRING_SPACE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SSTRING_PUT (TYPE_1__*,int) ; 
 int STRING_TOKEN ; 
 scalar_t__ atoi (scalar_t__*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lineno ; 
 int scan_ident (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int scan_string (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int skip_spaces (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ source_filename ; 
 scalar_t__ source_lineno ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

int
get_token (FILE *fp, sstring *s)
{
  int c;

  s->ptr = s->base;
 retry:
  c = ' ';
  c = skip_spaces (fp, c);
  if (c == '\n')
    {
      source_lineno++;
      lineno++;
      goto retry;
    }
  if (c == '#')
    {
      c = get_token (fp, s);
      if (c == INT_TOKEN)
	{
	  source_lineno = atoi (s->base) - 1; /* '\n' will add 1 */
	  get_token (fp, &source_filename);
	}
      for (;;)
	{
	  c = getc (fp);
	  if (c == EOF)
	    return EOF;
	  if (c == '\n')
	    {
	    source_lineno++;
	    lineno++;
	    goto retry;
	    }
	}
    }
  if (c == EOF)
    return EOF;
  if (ISDIGIT (c))
    {
      do
	{
	  SSTRING_PUT (s, c);
	  c = getc (fp);
	} while (c != EOF && ISDIGIT (c));
      ungetc (c, fp);
      c = INT_TOKEN;
      goto done;
    }
  if (ISIDST (c))
    {
      c = scan_ident (fp, s, c);
      ungetc (c, fp);
      return IDENTIFIER_TOKEN;
    }
  if (c == '\'' || c == '"')
    {
      c = scan_string (fp, s, c);
      ungetc (c, fp);
      return c == '\'' ? CHAR_TOKEN : STRING_TOKEN;
    }
  SSTRING_PUT (s, c);
 done:
  MAKE_SSTRING_SPACE (s, 1);
  *s->ptr = 0;
  return c;
}