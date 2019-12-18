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
struct radeon_device {int shutdown; int /*<<< orphan*/ * rmmio; int /*<<< orphan*/ * rio_mem; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_evict_vram (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_debugfs_remove_files (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  vga_client_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (int /*<<< orphan*/ ) ; 

void radeon_device_fini(struct radeon_device *rdev)
{
	DRM_INFO("radeon: finishing device.\n");
	rdev->shutdown = true;
	/* evict vram memory */
	radeon_bo_evict_vram(rdev);
	radeon_fini(rdev);
	vga_switcheroo_unregister_client(rdev->pdev);
	vga_client_register(rdev->pdev, NULL, NULL, NULL);
	if (rdev->rio_mem)
		pci_iounmap(rdev->pdev, rdev->rio_mem);
	rdev->rio_mem = NULL;
	iounmap(rdev->rmmio);
	rdev->rmmio = NULL;
	radeon_debugfs_remove_files(rdev);
}