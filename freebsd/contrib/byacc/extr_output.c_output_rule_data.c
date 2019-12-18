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
 int /*<<< orphan*/  end_table () ; 
 int nrules ; 
 int /*<<< orphan*/  output_YYINT_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_file ; 
 int /*<<< orphan*/  output_int (int) ; 
 int /*<<< orphan*/  output_newline () ; 
 size_t* rlhs ; 
 int* rrhs ; 
 int /*<<< orphan*/  start_int_table (char*,int) ; 
 size_t start_symbol ; 
 int* symbol_value ; 

__attribute__((used)) static void
output_rule_data(void)
{
    int i;
    int j;

    output_YYINT_typedef(output_file);

    start_int_table("lhs", symbol_value[start_symbol]);

    j = 10;
    for (i = 3; i < nrules; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	output_int(symbol_value[rlhs[i]]);
    }
    end_table();

    start_int_table("len", 2);

    j = 10;
    for (i = 3; i < nrules; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    j++;

	output_int(rrhs[i + 1] - rrhs[i] - 1);
    }
    end_table();
}