#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {scalar_t__ pseudo_palette; TYPE_2__ cmap; } ;
struct au1200fb_device {TYPE_1__ fb_info; int /*<<< orphan*/  fb_phys; scalar_t__ fb_mem; int /*<<< orphan*/  fb_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU1200_LCD_INT ; 
 int CONFIG_FB_AU1200_DEVS ; 
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 struct au1200fb_device* _au1200fb_devices ; 
 int /*<<< orphan*/  au1200_setpanel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_noncoherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_2__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 

__attribute__((used)) static int au1200fb_drv_remove(struct platform_device *dev)
{
	struct au1200fb_device *fbdev;
	int plane;

	if (!dev)
		return -ENODEV;

	/* Turn off the panel */
	au1200_setpanel(NULL);

	for (plane = 0; plane < CONFIG_FB_AU1200_DEVS; ++plane)
	{
		fbdev = &_au1200fb_devices[plane];

		/* Clean up all probe data */
		unregister_framebuffer(&fbdev->fb_info);
		if (fbdev->fb_mem)
			dma_free_noncoherent(&dev->dev,
					PAGE_ALIGN(fbdev->fb_len),
					fbdev->fb_mem, fbdev->fb_phys);
		if (fbdev->fb_info.cmap.len != 0)
			fb_dealloc_cmap(&fbdev->fb_info.cmap);
		if (fbdev->fb_info.pseudo_palette)
			kfree(fbdev->fb_info.pseudo_palette);
	}

	free_irq(AU1200_LCD_INT, (void *)dev);

	return 0;
}