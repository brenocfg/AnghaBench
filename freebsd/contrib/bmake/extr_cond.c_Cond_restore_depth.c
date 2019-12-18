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
 int /*<<< orphan*/  PARSE_FATAL ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,int,char*) ; 
 unsigned int cond_depth ; 
 unsigned int cond_min_depth ; 

void
Cond_restore_depth(unsigned int saved_depth)
{
    int open_conds = cond_depth - cond_min_depth;

    if (open_conds != 0 || saved_depth > cond_depth) {
	Parse_Error(PARSE_FATAL, "%d open conditional%s", open_conds,
		    open_conds == 1 ? "" : "s");
	cond_depth = cond_min_depth;
    }

    cond_min_depth = saved_depth;
}