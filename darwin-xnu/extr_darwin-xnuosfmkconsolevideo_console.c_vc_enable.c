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
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  v_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc_render_font (int /*<<< orphan*/ ) ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void
vc_enable(boolean_t enable)
{
	vc_render_font(enable ? vinfo.v_depth : 0);
}