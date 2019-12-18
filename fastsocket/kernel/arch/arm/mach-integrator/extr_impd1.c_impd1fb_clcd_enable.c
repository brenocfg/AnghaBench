#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct clcd_fb {TYPE_3__* panel; TYPE_2__* dev; } ;
struct TYPE_6__ {int connector; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int IMPD1_CTRL_DISP_ENABLE ; 
 int /*<<< orphan*/  IMPD1_CTRL_DISP_MASK ; 
 int /*<<< orphan*/  impd1_tweak_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void impd1fb_clcd_enable(struct clcd_fb *fb)
{
	impd1_tweak_control(fb->dev->dev.parent, IMPD1_CTRL_DISP_MASK,
			fb->panel->connector | IMPD1_CTRL_DISP_ENABLE);
}