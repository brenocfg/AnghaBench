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
struct nouveau_drm {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_switcheroo_ops ; 
 int /*<<< orphan*/  nouveau_vga_set_decode ; 
 int /*<<< orphan*/  vga_client_register (int /*<<< orphan*/ ,struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_switcheroo_register_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nouveau_vga_init(struct nouveau_drm *drm)
{
	struct drm_device *dev = drm->dev;
	vga_client_register(dev->pdev, dev, NULL, nouveau_vga_set_decode);
	vga_switcheroo_register_client(dev->pdev, &nouveau_switcheroo_ops);
}