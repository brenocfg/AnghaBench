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
struct cafe_camera {int nbufs; int /*<<< orphan*/ * dma_handles; } ;

/* Variables and functions */
 int /*<<< orphan*/  C1_TWOBUFS ; 
 int /*<<< orphan*/  REG_CTRL1 ; 
 int /*<<< orphan*/  REG_UBAR ; 
 int /*<<< orphan*/  REG_Y0BAR ; 
 int /*<<< orphan*/  REG_Y1BAR ; 
 int /*<<< orphan*/  REG_Y2BAR ; 
 int /*<<< orphan*/  cafe_reg_clear_bit (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_reg_set_bit (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_reg_write (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cafe_ctlr_dma(struct cafe_camera *cam)
{
	/*
	 * Store the first two Y buffers (we aren't supporting
	 * planar formats for now, so no UV bufs).  Then either
	 * set the third if it exists, or tell the controller
	 * to just use two.
	 */
	cafe_reg_write(cam, REG_Y0BAR, cam->dma_handles[0]);
	cafe_reg_write(cam, REG_Y1BAR, cam->dma_handles[1]);
	if (cam->nbufs > 2) {
		cafe_reg_write(cam, REG_Y2BAR, cam->dma_handles[2]);
		cafe_reg_clear_bit(cam, REG_CTRL1, C1_TWOBUFS);
	}
	else
		cafe_reg_set_bit(cam, REG_CTRL1, C1_TWOBUFS);
	cafe_reg_write(cam, REG_UBAR, 0); /* 32 bits only for now */
}