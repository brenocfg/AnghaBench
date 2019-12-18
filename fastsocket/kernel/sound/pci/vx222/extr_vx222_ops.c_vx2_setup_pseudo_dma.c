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
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  ICR_RREQ ; 
 int /*<<< orphan*/  ICR_TREQ ; 
 int /*<<< orphan*/  RESET_DMA ; 
 int /*<<< orphan*/  vx_outl (struct vx_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vx2_setup_pseudo_dma(struct vx_core *chip, int do_write)
{
	/* Interrupt mode and HREQ pin enabled for host transmit data transfers
	 * (in case of the use of the pseudo-dma facility).
	 */
	vx_outl(chip, ICR, do_write ? ICR_TREQ : ICR_RREQ);

	/* Reset the pseudo-dma register (in case of the use of the
	 * pseudo-dma facility).
	 */
	vx_outl(chip, RESET_DMA, 0);
}