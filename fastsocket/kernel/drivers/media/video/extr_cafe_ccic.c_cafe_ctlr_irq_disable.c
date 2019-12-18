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
struct cafe_camera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAMEIRQS ; 
 int /*<<< orphan*/  REG_IRQMASK ; 
 int /*<<< orphan*/  cafe_reg_clear_bit (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cafe_ctlr_irq_disable(struct cafe_camera *cam)
{
	cafe_reg_clear_bit(cam, REG_IRQMASK, FRAMEIRQS);
}