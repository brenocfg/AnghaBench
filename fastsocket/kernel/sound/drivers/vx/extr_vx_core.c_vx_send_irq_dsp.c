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
struct vx_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVR ; 
 int CVR_HC ; 
 int EIO ; 
 scalar_t__ VXP_IRQ_OFFSET ; 
 int /*<<< orphan*/  VX_CVR ; 
 scalar_t__ snd_vx_check_reg_bit (struct vx_core*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vx_has_new_dsp (struct vx_core*) ; 
 int /*<<< orphan*/  vx_outb (struct vx_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vx_send_irq_dsp(struct vx_core *chip, int num)
{
	int nirq;

	/* wait for Hc = 0 */
	if (snd_vx_check_reg_bit(chip, VX_CVR, CVR_HC, 0, 200) < 0)
		return -EIO;

	nirq = num;
	if (vx_has_new_dsp(chip))
		nirq += VXP_IRQ_OFFSET;
	vx_outb(chip, CVR, (nirq >> 1) | CVR_HC);
	return 0;
}