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

/* Variables and functions */
 int cirrusfb_set_par_foo (struct fb_info*) ; 

__attribute__((used)) static int cirrusfb_set_par(struct fb_info *info)
{
	cirrusfb_set_par_foo(info);
	return cirrusfb_set_par_foo(info);
}