#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fb_info {int dummy; } ;
struct display {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct aafb_info {TYPE_1__ cursor; struct display disp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ERASE ; 
 int /*<<< orphan*/  aafbcon_cursor (struct display*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int currcon ; 
 struct display* fb_display ; 

__attribute__((used)) static int aafb_update_var(int con, struct fb_info *info)
{
	struct aafb_info *ip = (struct aafb_info *)info;
	struct display *disp = (con < 0) ? &ip->disp : (fb_display + con);

	if (con == currcon)
		aafbcon_cursor(disp, CM_ERASE, ip->cursor.x, ip->cursor.y);

	return 0;
}