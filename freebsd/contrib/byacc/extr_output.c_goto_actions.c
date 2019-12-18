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
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEW2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Value_t ; 
 int default_goto (int) ; 
 int /*<<< orphan*/  end_table () ; 
 int /*<<< orphan*/  nstates ; 
 int nsyms ; 
 int /*<<< orphan*/  output_int (int) ; 
 int /*<<< orphan*/  output_newline () ; 
 int /*<<< orphan*/  save_column (int,int) ; 
 int /*<<< orphan*/  start_int_table (char*,int) ; 
 int start_symbol ; 
 int /*<<< orphan*/  state_count ; 

__attribute__((used)) static void
goto_actions(void)
{
    int i, j, k;

    state_count = NEW2(nstates, Value_t);

    k = default_goto(start_symbol + 1);
    start_int_table("dgoto", k);
    save_column(start_symbol + 1, k);

    j = 10;
    for (i = start_symbol + 2; i < nsyms; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	k = default_goto(i);
	output_int(k);
	save_column(i, k);
    }

    end_table();
    FREE(state_count);
}