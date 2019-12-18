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
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_error (char*) ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * text_file ; 
 int /*<<< orphan*/  write_code_lineno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
output_stored_text(FILE * fp)
{
    int c;
    FILE *in;

    rewind(text_file);
    if (text_file == NULL)
	open_error("text_file");
    in = text_file;
    if ((c = getc(in)) == EOF)
	return;
    putc_code(fp, c);
    while ((c = getc(in)) != EOF)
    {
	putc_code(fp, c);
    }
    write_code_lineno(fp);
}