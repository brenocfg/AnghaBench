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
struct vc_data {scalar_t__ vc_mode; TYPE_1__* vc_sw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* con_set_palette ) (struct vc_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ KD_GRAPHICS ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  color_table ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_palette(struct vc_data *vc)
{
	WARN_CONSOLE_UNLOCKED();

	if (vc->vc_mode != KD_GRAPHICS)
		vc->vc_sw->con_set_palette(vc, color_table);
}