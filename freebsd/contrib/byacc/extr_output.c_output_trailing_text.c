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
 int /*<<< orphan*/  code_file ; 
 int* cptr ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * input_file ; 
 scalar_t__ line ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  write_code_lineno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_input_lineno () ; 

__attribute__((used)) static void
output_trailing_text(void)
{
    int c, last;
    FILE *in;

    if (line == 0)
	return;

    in = input_file;
    c = *cptr;
    if (c == '\n')
    {
	++lineno;
	if ((c = getc(in)) == EOF)
	    return;
	write_input_lineno();
	putc_code(code_file, c);
	last = c;
    }
    else
    {
	write_input_lineno();
	do
	{
	    putc_code(code_file, c);
	}
	while ((c = *++cptr) != '\n');
	putc_code(code_file, c);
	last = '\n';
    }

    while ((c = getc(in)) != EOF)
    {
	putc_code(code_file, c);
	last = c;
    }

    if (last != '\n')
    {
	putc_code(code_file, '\n');
    }
    write_code_lineno(code_file);
}