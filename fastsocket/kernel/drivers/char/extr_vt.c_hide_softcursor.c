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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {int /*<<< orphan*/  vc_x; int /*<<< orphan*/  vc_y; TYPE_1__* vc_sw; scalar_t__ vc_pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* con_putc ) (struct vc_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ DO_UPDATE (struct vc_data*) ; 
 int /*<<< orphan*/  scr_writew (int,int /*<<< orphan*/ *) ; 
 int softcursor_original ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hide_softcursor(struct vc_data *vc)
{
	if (softcursor_original != -1) {
		scr_writew(softcursor_original, (u16 *)vc->vc_pos);
		if (DO_UPDATE(vc))
			vc->vc_sw->con_putc(vc, softcursor_original,
					vc->vc_y, vc->vc_x);
		softcursor_original = -1;
	}
}