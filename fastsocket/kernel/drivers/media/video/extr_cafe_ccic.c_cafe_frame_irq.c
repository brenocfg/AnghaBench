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
struct cafe_camera {unsigned int nbufs; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_DMA_ACTIVE ; 
 int /*<<< orphan*/  FRAMEIRQS ; 
 unsigned int IRQ_EOF0 ; 
 unsigned int IRQ_SOF0 ; 
 unsigned int IRQ_SOF1 ; 
 unsigned int IRQ_SOF2 ; 
 int /*<<< orphan*/  REG_IRQSTAT ; 
 int /*<<< orphan*/  cafe_frame_complete (struct cafe_camera*,unsigned int) ; 
 int /*<<< orphan*/  cafe_reg_write (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cafe_frame_irq(struct cafe_camera *cam, unsigned int irqs)
{
	unsigned int frame;

	cafe_reg_write(cam, REG_IRQSTAT, FRAMEIRQS); /* Clear'em all */
	/*
	 * Handle any frame completions.  There really should
	 * not be more than one of these, or we have fallen
	 * far behind.
	 */
	for (frame = 0; frame < cam->nbufs; frame++)
		if (irqs & (IRQ_EOF0 << frame))
			cafe_frame_complete(cam, frame);
	/*
	 * If a frame starts, note that we have DMA active.  This
	 * code assumes that we won't get multiple frame interrupts
	 * at once; may want to rethink that.
	 */
	if (irqs & (IRQ_SOF0 | IRQ_SOF1 | IRQ_SOF2))
		set_bit(CF_DMA_ACTIVE, &cam->flags);
}