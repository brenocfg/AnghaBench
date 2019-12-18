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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  init; } ;
struct TYPE_4__ {TYPE_1__ ram; int /*<<< orphan*/  memtype_valid; } ;
struct nvc0_fb_priv {TYPE_2__ base; int /*<<< orphan*/  r100c10; int /*<<< orphan*/  r100c10_page; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  alloc_page (int) ; 
 int nouveau_fb_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nvc0_fb_priv**) ; 
 int nouveau_fb_preinit (TYPE_2__*) ; 
 int /*<<< orphan*/  nv50_fb_vram_del ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 
 struct nouveau_object* nv_object (struct nvc0_fb_priv*) ; 
 int /*<<< orphan*/  nvc0_fb_memtype_valid ; 
 int /*<<< orphan*/  nvc0_fb_vram_init ; 
 int /*<<< orphan*/  nvc0_fb_vram_new ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvc0_fb_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nvc0_fb_priv *priv;
	int ret;

	ret = nouveau_fb_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.memtype_valid = nvc0_fb_memtype_valid;
	priv->base.ram.init = nvc0_fb_vram_init;
	priv->base.ram.get = nvc0_fb_vram_new;
	priv->base.ram.put = nv50_fb_vram_del;

	priv->r100c10_page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!priv->r100c10_page)
		return -ENOMEM;

	priv->r100c10 = pci_map_page(device->pdev, priv->r100c10_page, 0,
				     PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
	if (pci_dma_mapping_error(device->pdev, priv->r100c10))
		return -EFAULT;

	return nouveau_fb_preinit(&priv->base);
}