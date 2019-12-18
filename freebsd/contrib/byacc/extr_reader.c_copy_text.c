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
struct ainfo {int a_line; int a_cptr; int /*<<< orphan*/  a_lineno; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int) ; 
 char R_CURL ; 
 char* copy_comment () ; 
 char* copy_string (int) ; 
 char* cptr ; 
 int dup_line () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_line () ; 
 int /*<<< orphan*/  input_file_name ; 
 int /*<<< orphan*/  lflag ; 
 char* line ; 
 char* line_format ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * text_file ; 
 int /*<<< orphan*/  unterminated_text (struct ainfo*) ; 

__attribute__((used)) static void
copy_text(void)
{
    int c;
    FILE *f = text_file;
    int need_newline = 0;
    struct ainfo a;
    a.a_lineno = lineno;
    a.a_line = dup_line();
    a.a_cptr = a.a_line + (cptr - line - 2);

    if (*cptr == '\n')
    {
	get_line();
	if (line == NULL)
	    unterminated_text(&a);
    }
    if (!lflag)
	fprintf(f, line_format, lineno, input_file_name);

  loop:
    c = *cptr++;
    switch (c)
    {
    case '\n':
	putc('\n', f);
	need_newline = 0;
	get_line();
	if (line)
	    goto loop;
	unterminated_text(&a);

    case '\'':
    case '"':
	putc(c, f);
	{
	    char *s = copy_string(c);
	    fputs(s, f);
	    free(s);
	}
	need_newline = 1;
	goto loop;

    case '/':
	putc(c, f);
	{
	    char *s = copy_comment();
	    fputs(s, f);
	    free(s);
	}
	need_newline = 1;
	goto loop;

    case '%':
    case '\\':
	if (*cptr == R_CURL)
	{
	    if (need_newline)
		putc('\n', f);
	    ++cptr;
	    FREE(a.a_line);
	    return;
	}
	/* FALLTHRU */

    default:
	putc(c, f);
	need_newline = 1;
	goto loop;
    }
}