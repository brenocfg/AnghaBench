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
typedef  int u8 ;
struct drm_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int GRDOM_MEDIA ; 
 int GRDOM_RENDER ; 
 int GRDOM_RESET_ENABLE ; 
 int /*<<< orphan*/  I965_GDRST ; 
 int /*<<< orphan*/  i965_reset_complete (struct drm_device*) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wait_for (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i965_do_reset(struct drm_device *dev)
{
	int ret;
	u8 gdrst;

	/*
	 * Set the domains we want to reset (GRDOM/bits 2 and 3) as
	 * well as the reset bit (GR/bit 0).  Setting the GR bit
	 * triggers the reset; when done, the hardware will clear it.
	 */
	pci_read_config_byte(dev->pdev, I965_GDRST, &gdrst);
	pci_write_config_byte(dev->pdev, I965_GDRST,
			      gdrst | GRDOM_RENDER |
			      GRDOM_RESET_ENABLE);
	ret =  wait_for(i965_reset_complete(dev), 500);
	if (ret)
		return ret;

	/* We can't reset render&media without also resetting display ... */
	pci_read_config_byte(dev->pdev, I965_GDRST, &gdrst);
	pci_write_config_byte(dev->pdev, I965_GDRST,
			      gdrst | GRDOM_MEDIA |
			      GRDOM_RESET_ENABLE);

	return wait_for(i965_reset_complete(dev), 500);
}