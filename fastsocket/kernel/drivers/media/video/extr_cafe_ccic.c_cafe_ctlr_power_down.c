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
struct cafe_camera {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  C1_PWRDWN ; 
 int GFCR_GPIO_ON ; 
 int GGPIO_OUT ; 
 int GPR_C0EN ; 
 int GPR_C1 ; 
 int GPR_C1EN ; 
 int /*<<< orphan*/  REG_CTRL1 ; 
 int /*<<< orphan*/  REG_GL_FCR ; 
 int /*<<< orphan*/  REG_GL_GPIOR ; 
 int /*<<< orphan*/  REG_GPR ; 
 int /*<<< orphan*/  cafe_reg_set_bit (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_reg_write (struct cafe_camera*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cafe_ctlr_power_down(struct cafe_camera *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->dev_lock, flags);
	cafe_reg_write(cam, REG_GPR, GPR_C1EN|GPR_C0EN|GPR_C1);
	cafe_reg_write(cam, REG_GL_FCR, GFCR_GPIO_ON);
	cafe_reg_write(cam, REG_GL_GPIOR, GGPIO_OUT);
	cafe_reg_set_bit(cam, REG_CTRL1, C1_PWRDWN);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
}