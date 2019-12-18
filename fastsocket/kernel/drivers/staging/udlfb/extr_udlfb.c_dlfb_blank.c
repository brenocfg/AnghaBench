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
struct fb_info {struct dlfb_data* par; } ;
struct dlfb_data {char* buf; } ;

/* Variables and functions */
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  dlfb_bulk_msg (struct dlfb_data*,int) ; 
 char* dlfb_set_register (char*,int,int) ; 

__attribute__((used)) static int dlfb_blank(int blank_mode, struct fb_info *info)
{
	struct dlfb_data *dev_info = info->par;
	char *bufptr = dev_info->buf;

	bufptr = dlfb_set_register(bufptr, 0xFF, 0x00);
	if (blank_mode != FB_BLANK_UNBLANK) {
		bufptr = dlfb_set_register(bufptr, 0x1F, 0x01);
	} else {
		bufptr = dlfb_set_register(bufptr, 0x1F, 0x00);
	}
	bufptr = dlfb_set_register(bufptr, 0xFF, 0xFF);

	dlfb_bulk_msg(dev_info, bufptr - dev_info->buf);

	return 0;
}