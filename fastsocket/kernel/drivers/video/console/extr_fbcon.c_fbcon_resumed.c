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
struct vc_data {int dummy; } ;
struct fbcon_ops {size_t currcon; } ;
struct fb_info {struct fbcon_ops* fbcon_par; } ;
struct TYPE_2__ {struct vc_data* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_screen (struct vc_data*) ; 
 TYPE_1__* vc_cons ; 

__attribute__((used)) static void fbcon_resumed(struct fb_info *info)
{
	struct vc_data *vc;
	struct fbcon_ops *ops = info->fbcon_par;

	if (!ops || ops->currcon < 0)
		return;
	vc = vc_cons[ops->currcon].d;

	update_screen(vc);
}