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
 int /*<<< orphan*/  C0_ENABLE ; 
 int /*<<< orphan*/  C1_PWRDWN ; 
 int /*<<< orphan*/  CLK_DIV_MASK ; 
 int GCSR_CCIC_EN ; 
 int GCSR_MRC ; 
 int GCSR_MRS ; 
 int GCSR_SRC ; 
 int GCSR_SRS ; 
 int /*<<< orphan*/  GIMSK_CCIC_EN ; 
 int /*<<< orphan*/  REG_CLKCTRL ; 
 int /*<<< orphan*/  REG_CTRL0 ; 
 int /*<<< orphan*/  REG_CTRL1 ; 
 int REG_GL_CSR ; 
 int /*<<< orphan*/  REG_GL_IMASK ; 
 int REG_IRQMASK ; 
 int /*<<< orphan*/  cafe_reg_clear_bit (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_reg_set_bit (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_reg_write (struct cafe_camera*,int,int) ; 
 int /*<<< orphan*/  cafe_reg_write_mask (struct cafe_camera*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cafe_ctlr_init(struct cafe_camera *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->dev_lock, flags);
	/*
	 * Added magic to bring up the hardware on the B-Test board
	 */
	cafe_reg_write(cam, 0x3038, 0x8);
	cafe_reg_write(cam, 0x315c, 0x80008);
	/*
	 * Go through the dance needed to wake the device up.
	 * Note that these registers are global and shared
	 * with the NAND and SD devices.  Interaction between the
	 * three still needs to be examined.
	 */
	cafe_reg_write(cam, REG_GL_CSR, GCSR_SRS|GCSR_MRS); /* Needed? */
	cafe_reg_write(cam, REG_GL_CSR, GCSR_SRC|GCSR_MRC);
	cafe_reg_write(cam, REG_GL_CSR, GCSR_SRC|GCSR_MRS);
	/*
	 * Here we must wait a bit for the controller to come around.
	 */
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	msleep(5);
	spin_lock_irqsave(&cam->dev_lock, flags);

	cafe_reg_write(cam, REG_GL_CSR, GCSR_CCIC_EN|GCSR_SRC|GCSR_MRC);
	cafe_reg_set_bit(cam, REG_GL_IMASK, GIMSK_CCIC_EN);
	/*
	 * Make sure it's not powered down.
	 */
	cafe_reg_clear_bit(cam, REG_CTRL1, C1_PWRDWN);
	/*
	 * Turn off the enable bit.  It sure should be off anyway,
	 * but it's good to be sure.
	 */
	cafe_reg_clear_bit(cam, REG_CTRL0, C0_ENABLE);
	/*
	 * Mask all interrupts.
	 */
	cafe_reg_write(cam, REG_IRQMASK, 0);
	/*
	 * Clock the sensor appropriately.  Controller clock should
	 * be 48MHz, sensor "typical" value is half that.
	 */
	cafe_reg_write_mask(cam, REG_CLKCTRL, 2, CLK_DIV_MASK);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
}