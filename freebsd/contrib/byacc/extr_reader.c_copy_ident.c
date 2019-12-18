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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int* cptr ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  lineno ; 
 int nextc () ; 
 int /*<<< orphan*/  outline ; 
 int /*<<< orphan*/ * output_file ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syntax_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  unexpected_EOF () ; 

__attribute__((used)) static void
copy_ident(void)
{
    int c;
    FILE *f = output_file;

    c = nextc();
    if (c == EOF)
	unexpected_EOF();
    if (c != '"')
	syntax_error(lineno, line, cptr);
    ++outline;
    fprintf(f, "#ident \"");
    for (;;)
    {
	c = *++cptr;
	if (c == '\n')
	{
	    fprintf(f, "\"\n");
	    return;
	}
	putc(c, f);
	if (c == '"')
	{
	    putc('\n', f);
	    ++cptr;
	    return;
	}
    }
}