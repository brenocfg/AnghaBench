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
 scalar_t__* defred ; 
 int /*<<< orphan*/  end_table () ; 
 int nstates ; 
 int /*<<< orphan*/  output_int (scalar_t__) ; 
 int /*<<< orphan*/  output_newline () ; 
 int /*<<< orphan*/  start_int_table (char*,scalar_t__) ; 

__attribute__((used)) static void
output_yydefred(void)
{
    int i, j;

    start_int_table("defred", (defred[0] ? defred[0] - 2 : 0));

    j = 10;
    for (i = 1; i < nstates; i++)
    {
	if (j < 10)
	    ++j;
	else
	{
	    output_newline();
	    j = 1;
	}

	output_int((defred[i] ? defred[i] - 2 : 0));
    }

    end_table();
}