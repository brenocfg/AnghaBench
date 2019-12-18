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
 int EOF ; 
 int /*<<< orphan*/  action_file ; 
 int /*<<< orphan*/  code_file ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_code_lineno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_semantic_actions(void)
{
    int c, last;

    rewind(action_file);
    if ((c = getc(action_file)) == EOF)
	return;

    last = c;
    putc_code(code_file, c);
    while ((c = getc(action_file)) != EOF)
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