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
 int GGPIO_VAL ; 
 int GPR_C0 ; 
 int GPR_C0EN ; 
 int GPR_C1EN ; 
 int /*<<< orphan*/  REG_CTRL1 ; 
 int /*<<< orphan*/  REG_GL_FCR ; 
 int /*<<< orphan*/  REG_GL_GPIOR ; 
 int /*<<< orphan*/  REG_GPR ; 
 int /*<<< orphan*/  cafe_reg_clear_bit (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_reg_write (struct cafe_camera*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cafe_ctlr_power_up(struct cafe_camera *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->dev_lock, flags);
	cafe_reg_clear_bit(cam, REG_CTRL1, C1_PWRDWN);
	/*
	 * Part one of the sensor dance: turn the global
	 * GPIO signal on.
	 */
	cafe_reg_write(cam, REG_GL_FCR, GFCR_GPIO_ON);
	cafe_reg_write(cam, REG_GL_GPIOR, GGPIO_OUT|GGPIO_VAL);
	/*
	 * Put the sensor into operational mode (assumes OLPC-style
	 * wiring).  Control 0 is reset - set to 1 to operate.
	 * Control 1 is power down, set to 0 to operate.
	 */
	cafe_reg_write(cam, REG_GPR, GPR_C1EN|GPR_C0EN); /* pwr up, reset */
/*	mdelay(1); */ /* Marvell says 1ms will do it */
	cafe_reg_write(cam, REG_GPR, GPR_C1EN|GPR_C0EN|GPR_C0);
/*	mdelay(1); */ /* Enough? */
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	msleep(5); /* Just to be sure */
}