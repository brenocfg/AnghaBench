#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct drm_clip_rect {scalar_t__ y2; scalar_t__ x2; scalar_t__ y1; scalar_t__ x1; } ;
struct TYPE_5__ {int new_drawctrl0; int new_drawctrl1; int drawctrl0; int drawctrl1; } ;
struct TYPE_6__ {TYPE_1__ s4; } ;
struct TYPE_7__ {int waiting; TYPE_2__ state; } ;
typedef  TYPE_3__ drm_savage_private_t ;

/* Variables and functions */
 int BCI_CMD_WAIT ; 
 int BCI_CMD_WAIT_3D ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_COMMIT () ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  DMA_SET_REGISTERS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_WRITE (int) ; 
 int /*<<< orphan*/  SAVAGE_DRAWCTRL0_S4 ; 
 int SAVAGE_SCISSOR_MASK_S4 ; 

void savage_emit_clip_rect_s4(drm_savage_private_t * dev_priv,
			      const struct drm_clip_rect * pbox)
{
	uint32_t drawctrl0 = dev_priv->state.s4.new_drawctrl0;
	uint32_t drawctrl1 = dev_priv->state.s4.new_drawctrl1;
	drawctrl0 = (drawctrl0 & ~SAVAGE_SCISSOR_MASK_S4) |
	    ((uint32_t) pbox->x1 & 0x000007ff) |
	    (((uint32_t) pbox->y1 << 12) & 0x00fff000);
	drawctrl1 = (drawctrl1 & ~SAVAGE_SCISSOR_MASK_S4) |
	    (((uint32_t) pbox->x2 - 1) & 0x000007ff) |
	    ((((uint32_t) pbox->y2 - 1) << 12) & 0x00fff000);
	if (drawctrl0 != dev_priv->state.s4.drawctrl0 ||
	    drawctrl1 != dev_priv->state.s4.drawctrl1) {
		DMA_LOCALS;
		BEGIN_DMA(4);
		DMA_WRITE(BCI_CMD_WAIT | BCI_CMD_WAIT_3D);
		DMA_SET_REGISTERS(SAVAGE_DRAWCTRL0_S4, 2);
		DMA_WRITE(drawctrl0);
		DMA_WRITE(drawctrl1);
		dev_priv->state.s4.drawctrl0 = drawctrl0;
		dev_priv->state.s4.drawctrl1 = drawctrl1;
		dev_priv->waiting = 1;
		DMA_COMMIT();
	}
}