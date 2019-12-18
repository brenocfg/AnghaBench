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
 int /*<<< orphan*/ * check ; 
 int /*<<< orphan*/  end_table () ; 
 int high ; 
 int /*<<< orphan*/  output_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_newline () ; 
 int /*<<< orphan*/  start_int_table (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_check(void)
{
    int i;
    int j;

    start_int_table("check", check[0]);

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

	output_int(check[i]);
    }

    end_table();
    FREE(check);
}