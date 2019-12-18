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
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MaxIntermediateResult ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

void
ErrorSizeLimitIsExceeded()
{
	ereport(ERROR, (errmsg("the intermediate result size exceeds "
						   "citus.max_intermediate_result_size (currently %d kB)",
						   MaxIntermediateResult),
					errdetail("Citus restricts the size of intermediate "
							  "results of complex subqueries and CTEs to "
							  "avoid accidentally pulling large result sets "
							  "into once place."),
					errhint("To run the current query, set "
							"citus.max_intermediate_result_size to a higher"
							" value or -1 to disable.")));
}