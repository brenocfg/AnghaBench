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
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int MAXYYINT ; 
 int /*<<< orphan*/  code_file ; 
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  end_table () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int high ; 
 int /*<<< orphan*/  outline ; 
 int /*<<< orphan*/  output_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_newline () ; 
 int /*<<< orphan*/  start_int_table (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * table ; 

__attribute__((used)) static void
output_table(void)
{
    int i;
    int j;

    if (high >= MAXYYINT)
    {
	fprintf(stderr, "YYTABLESIZE: %ld\n", high);
	fprintf(stderr, "Table is longer than %d elements.\n", MAXYYINT);
	done(1);
    }

    ++outline;
    fprintf(code_file, "#define YYTABLESIZE %ld\n", high);
    start_int_table("table", table[0]);

    j = 10;
    for (i = 1; i <= high; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	output_int(table[i]);
    }

    end_table();
    FREE(table);
}