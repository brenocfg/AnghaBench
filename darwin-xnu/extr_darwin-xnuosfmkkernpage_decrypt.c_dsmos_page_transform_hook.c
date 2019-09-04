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
typedef  int /*<<< orphan*/  dsmos_page_transform_hook_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsmos_hook ; 
 int /*<<< orphan*/  printf (char*) ; 

void
dsmos_page_transform_hook(dsmos_page_transform_hook_t hook)
{

	printf("DSMOS has arrived\n");
	/* set the hook now - new callers will run with it */
	dsmos_hook = hook;
}