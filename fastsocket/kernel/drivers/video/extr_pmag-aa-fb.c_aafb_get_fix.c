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
struct fb_info {int dummy; } ;
struct fb_fix_screeninfo {int ypanstep; int ywrapstep; int line_length; int /*<<< orphan*/  accel; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct aafb_info {int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_MONO10 ; 
 int /*<<< orphan*/  memset (struct fb_fix_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int aafb_get_fix(struct fb_fix_screeninfo *fix, int con,
			struct fb_info *info)
{
	struct aafb_info *ip = (struct aafb_info *)info;

	memset(fix, 0, sizeof(struct fb_fix_screeninfo));
	strcpy(fix->id, "PMAG-AA");
	fix->smem_start = ip->fb_start;
	fix->smem_len = ip->fb_size;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->ypanstep = 1;
	fix->ywrapstep = 1;
	fix->visual = FB_VISUAL_MONO10;
	fix->line_length = 1280;
	fix->accel = FB_ACCEL_NONE;

	return 0;
}