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
typedef  int /*<<< orphan*/  u16 ;
struct fb_info {int /*<<< orphan*/  fix; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int FBCON_ATTRIBUTE_BOLD ; 
 int FBCON_ATTRIBUTE_REVERSE ; 
 int FBCON_ATTRIBUTE_UNDERLINE ; 
 scalar_t__ attr_bold (int /*<<< orphan*/ ) ; 
 scalar_t__ attr_reverse (int /*<<< orphan*/ ) ; 
 scalar_t__ attr_underline (int /*<<< orphan*/ ) ; 
 int fb_get_color_depth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_attribute(struct fb_info *info, u16 c)
{
	int attribute = 0;

	if (fb_get_color_depth(&info->var, &info->fix) == 1) {
		if (attr_underline(c))
			attribute |= FBCON_ATTRIBUTE_UNDERLINE;
		if (attr_reverse(c))
			attribute |= FBCON_ATTRIBUTE_REVERSE;
		if (attr_bold(c))
			attribute |= FBCON_ATTRIBUTE_BOLD;
	}

	return attribute;
}