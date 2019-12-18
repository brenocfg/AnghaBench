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
 int /*<<< orphan*/  WCB_B_BIT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gp2x_screens ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int warm_change_cb_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void gp2x_make_fb_bufferable(int yes)
{
	int ret = 0;
	
	yes = yes ? 1 : 0;
	ret |= warm_change_cb_range(WCB_B_BIT, yes, gp2x_screens[0], 320*240*2);
	ret |= warm_change_cb_range(WCB_B_BIT, yes, gp2x_screens[1], 320*240*2);
	ret |= warm_change_cb_range(WCB_B_BIT, yes, gp2x_screens[2], 320*240*2);
	ret |= warm_change_cb_range(WCB_B_BIT, yes, gp2x_screens[3], 320*240*2);

	if (ret)
		fprintf(stderr, "could not make fb buferable.\n");
	else
		printf("made fb buferable.\n");
}