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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  end_dialog () ; 
 int /*<<< orphan*/  ignore_unknown ; 

__attribute__((used)) static void
IgnoreNonScreen(char **argv, int offset)
{
    if (argv[offset + 1] == 0) {
	ignore_unknown = TRUE;
	end_dialog();
    }
}