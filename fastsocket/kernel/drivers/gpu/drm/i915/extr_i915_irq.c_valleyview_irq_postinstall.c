#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct drm_device {int /*<<< orphan*/  pdev; scalar_t__ dev_private; } ;
struct TYPE_5__ {int irq_mask; int gt_irq_mask; TYPE_1__* dev; scalar_t__* pipestat; } ;
typedef  TYPE_2__ drm_i915_private_t ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPINVGTT ; 
 int DPINVGTT_EN_MASK ; 
 int DPINVGTT_STATUS_MASK ; 
 int GEN6_BLITTER_USER_INTERRUPT ; 
 int GEN6_BSD_USER_INTERRUPT ; 
 int /*<<< orphan*/  GTIER ; 
 int /*<<< orphan*/  GTIIR ; 
 int /*<<< orphan*/  GTIMR ; 
 int GT_USER_INTERRUPT ; 
 int I915_DISPLAY_PIPE_A_EVENT_INTERRUPT ; 
 int I915_DISPLAY_PIPE_A_VBLANK_INTERRUPT ; 
 int I915_DISPLAY_PIPE_B_EVENT_INTERRUPT ; 
 int I915_DISPLAY_PIPE_B_VBLANK_INTERRUPT ; 
 int I915_DISPLAY_PORT_INTERRUPT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int MASTER_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  PIPESTAT (int) ; 
 int PIPE_GMBUS_EVENT_ENABLE ; 
 int PLANE_FLIP_DONE_INT_EN_VLV ; 
 int /*<<< orphan*/  PORT_HOTPLUG_EN ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_IER ; 
 int /*<<< orphan*/  VLV_IIR ; 
 int /*<<< orphan*/  VLV_IMR ; 
 int /*<<< orphan*/  VLV_MASTER_IER ; 
 int /*<<< orphan*/  i915_enable_pipestat (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int valleyview_irq_postinstall(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	u32 enable_mask;
	u32 pipestat_enable = PLANE_FLIP_DONE_INT_EN_VLV;
	u32 render_irqs;
	u16 msid;

	enable_mask = I915_DISPLAY_PORT_INTERRUPT;
	enable_mask |= I915_DISPLAY_PIPE_A_EVENT_INTERRUPT |
		I915_DISPLAY_PIPE_A_VBLANK_INTERRUPT |
		I915_DISPLAY_PIPE_B_EVENT_INTERRUPT |
		I915_DISPLAY_PIPE_B_VBLANK_INTERRUPT;

	/*
	 *Leave vblank interrupts masked initially.  enable/disable will
	 * toggle them based on usage.
	 */
	dev_priv->irq_mask = (~enable_mask) |
		I915_DISPLAY_PIPE_A_VBLANK_INTERRUPT |
		I915_DISPLAY_PIPE_B_VBLANK_INTERRUPT;

	dev_priv->pipestat[0] = 0;
	dev_priv->pipestat[1] = 0;

	/* Hack for broken MSIs on VLV */
	pci_write_config_dword(dev_priv->dev->pdev, 0x94, 0xfee00000);
	pci_read_config_word(dev->pdev, 0x98, &msid);
	msid &= 0xff; /* mask out delivery bits */
	msid |= (1<<14);
	pci_write_config_word(dev_priv->dev->pdev, 0x98, msid);

	I915_WRITE(PORT_HOTPLUG_EN, 0);
	POSTING_READ(PORT_HOTPLUG_EN);

	I915_WRITE(VLV_IMR, dev_priv->irq_mask);
	I915_WRITE(VLV_IER, enable_mask);
	I915_WRITE(VLV_IIR, 0xffffffff);
	I915_WRITE(PIPESTAT(0), 0xffff);
	I915_WRITE(PIPESTAT(1), 0xffff);
	POSTING_READ(VLV_IER);

	i915_enable_pipestat(dev_priv, 0, pipestat_enable);
	i915_enable_pipestat(dev_priv, 0, PIPE_GMBUS_EVENT_ENABLE);
	i915_enable_pipestat(dev_priv, 1, pipestat_enable);

	I915_WRITE(VLV_IIR, 0xffffffff);
	I915_WRITE(VLV_IIR, 0xffffffff);

	I915_WRITE(GTIIR, I915_READ(GTIIR));
	I915_WRITE(GTIMR, dev_priv->gt_irq_mask);

	render_irqs = GT_USER_INTERRUPT | GEN6_BSD_USER_INTERRUPT |
		GEN6_BLITTER_USER_INTERRUPT;
	I915_WRITE(GTIER, render_irqs);
	POSTING_READ(GTIER);

	/* ack & enable invalid PTE error interrupts */
#if 0 /* FIXME: add support to irq handler for checking these bits */
	I915_WRITE(DPINVGTT, DPINVGTT_STATUS_MASK);
	I915_WRITE(DPINVGTT, DPINVGTT_EN_MASK);
#endif

	I915_WRITE(VLV_MASTER_IER, MASTER_INTERRUPT_ENABLE);

	return 0;
}