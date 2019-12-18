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
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ PROGRESS_DELAY ; 
 scalar_t__ pt_begin ; 
 int /*<<< orphan*/  pt_shown ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
start_progress_timer(void)
{
	pt_begin = time(NULL) + PROGRESS_DELAY;
	pt_shown = B_FALSE;
}