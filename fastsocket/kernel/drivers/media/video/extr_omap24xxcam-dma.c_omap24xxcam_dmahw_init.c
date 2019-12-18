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

/* Variables and functions */
 int /*<<< orphan*/  CAMDMA_GCR ; 
 int /*<<< orphan*/  CAMDMA_GCR_MAX_CHANNEL_FIFO_DEPTH ; 
 int /*<<< orphan*/  CAMDMA_IRQENABLE_L0 ; 
 int /*<<< orphan*/  CAMDMA_OCP_SYSCONFIG ; 
 int CAMDMA_OCP_SYSCONFIG_AUTOIDLE ; 
 int CAMDMA_OCP_SYSCONFIG_MIDLEMODE_FSTANDBY ; 
 int CAMDMA_OCP_SYSCONFIG_SIDLEMODE_FIDLE ; 
 int /*<<< orphan*/  omap24xxcam_reg_merge (unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap24xxcam_reg_out (unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap24xxcam_dmahw_init(unsigned long base)
{
	omap24xxcam_reg_out(base, CAMDMA_OCP_SYSCONFIG,
			    CAMDMA_OCP_SYSCONFIG_MIDLEMODE_FSTANDBY
			    | CAMDMA_OCP_SYSCONFIG_SIDLEMODE_FIDLE
			    | CAMDMA_OCP_SYSCONFIG_AUTOIDLE);

	omap24xxcam_reg_merge(base, CAMDMA_GCR, 0x10,
			      CAMDMA_GCR_MAX_CHANNEL_FIFO_DEPTH);

	omap24xxcam_reg_out(base, CAMDMA_IRQENABLE_L0, 0xf);
}