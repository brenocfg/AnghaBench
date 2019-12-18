#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fb_info {int dummy; } ;
struct display {TYPE_2__* conp; } ;
struct aafb_info {struct display disp; } ;
struct TYPE_4__ {TYPE_1__* vc_sw; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* con_cursor ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ERASE ; 
 int /*<<< orphan*/  aafb_set_disp (struct display*,int,struct aafb_info*) ; 
 int currcon ; 
 struct display* fb_display ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aafb_switch(int con, struct fb_info *info)
{
	struct aafb_info *ip = (struct aafb_info *)info;
	struct display *old = (currcon < 0) ? &ip->disp : (fb_display + currcon);
	struct display *new = (con < 0) ? &ip->disp : (fb_display + con);

	if (old->conp && old->conp->vc_sw && old->conp->vc_sw->con_cursor)
		old->conp->vc_sw->con_cursor(old->conp, CM_ERASE);

	/* Set the current console. */
	currcon = con;
	aafb_set_disp(new, con, ip);

	return 0;
}