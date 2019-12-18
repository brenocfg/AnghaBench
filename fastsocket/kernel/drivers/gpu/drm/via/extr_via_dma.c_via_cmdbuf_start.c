#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int dma_offset; int dma_high; int dma_diff; int* hw_addr_ptr; char volatile* dma_ptr; scalar_t__ agpAddr; scalar_t__ last_pause_ptr; scalar_t__ dma_low; } ;
typedef  TYPE_1__ drm_via_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WRITEMEMORYBARRIER () ; 
 int /*<<< orphan*/  HC_HAGPBpID_PAUSE ; 
 int HC_HAGPCMNT_MASK ; 
 int HC_ParaType_PreCR ; 
 int HC_SubA_HAGPBendL ; 
 int HC_SubA_HAGPBstL ; 
 int HC_SubA_HAGPCMNT ; 
 int VIA_READ (int) ; 
 int VIA_REG_TRANSET ; 
 int VIA_REG_TRANSPACE ; 
 int /*<<< orphan*/  VIA_WRITE (int,int) ; 
 scalar_t__ via_align_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  via_flush_write_combine () ; 

__attribute__((used)) static void via_cmdbuf_start(drm_via_private_t *dev_priv)
{
	uint32_t pause_addr_lo, pause_addr_hi;
	uint32_t start_addr, start_addr_lo;
	uint32_t end_addr, end_addr_lo;
	uint32_t command;
	uint32_t agp_base;
	uint32_t ptr;
	uint32_t reader;
	int count;

	dev_priv->dma_low = 0;

	agp_base = dev_priv->dma_offset + (uint32_t) dev_priv->agpAddr;
	start_addr = agp_base;
	end_addr = agp_base + dev_priv->dma_high;

	start_addr_lo = ((HC_SubA_HAGPBstL << 24) | (start_addr & 0xFFFFFF));
	end_addr_lo = ((HC_SubA_HAGPBendL << 24) | (end_addr & 0xFFFFFF));
	command = ((HC_SubA_HAGPCMNT << 24) | (start_addr >> 24) |
		   ((end_addr & 0xff000000) >> 16));

	dev_priv->last_pause_ptr =
	    via_align_cmd(dev_priv, HC_HAGPBpID_PAUSE, 0,
			  &pause_addr_hi, &pause_addr_lo, 1) - 1;

	via_flush_write_combine();
	(void) *(volatile uint32_t *)dev_priv->last_pause_ptr;

	VIA_WRITE(VIA_REG_TRANSET, (HC_ParaType_PreCR << 16));
	VIA_WRITE(VIA_REG_TRANSPACE, command);
	VIA_WRITE(VIA_REG_TRANSPACE, start_addr_lo);
	VIA_WRITE(VIA_REG_TRANSPACE, end_addr_lo);

	VIA_WRITE(VIA_REG_TRANSPACE, pause_addr_hi);
	VIA_WRITE(VIA_REG_TRANSPACE, pause_addr_lo);
	DRM_WRITEMEMORYBARRIER();
	VIA_WRITE(VIA_REG_TRANSPACE, command | HC_HAGPCMNT_MASK);
	VIA_READ(VIA_REG_TRANSPACE);

	dev_priv->dma_diff = 0;

	count = 10000000;
	while (!(VIA_READ(0x41c) & 0x80000000) && count--);

	reader = *(dev_priv->hw_addr_ptr);
	ptr = ((volatile char *)dev_priv->last_pause_ptr - dev_priv->dma_ptr) +
	    dev_priv->dma_offset + (uint32_t) dev_priv->agpAddr + 4;

	/*
	 * This is the difference between where we tell the
	 * command reader to pause and where it actually pauses.
	 * This differs between hw implementation so we need to
	 * detect it.
	 */

	dev_priv->dma_diff = ptr - reader;
}