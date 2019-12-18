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
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int use_pager ; 

__attribute__((used)) static void commit_pager_choice(void)
{
	switch (use_pager) {
	case 0:
		setenv("PERF_PAGER", "cat", 1);
		break;
	case 1:
		/* setup_pager(); */
		break;
	default:
		break;
	}
}