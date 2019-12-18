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
struct nv50_fb_priv {int /*<<< orphan*/  base; scalar_t__ r100c08_page; int /*<<< orphan*/  r100c08; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_fb_destroy (int /*<<< orphan*/ *) ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv50_fb_dtor(struct nouveau_object *object)
{
	struct nouveau_device *device = nv_device(object);
	struct nv50_fb_priv *priv = (void *)object;

	if (priv->r100c08_page) {
		pci_unmap_page(device->pdev, priv->r100c08, PAGE_SIZE,
			       PCI_DMA_BIDIRECTIONAL);
		__free_page(priv->r100c08_page);
	}

	nouveau_fb_destroy(&priv->base);
}