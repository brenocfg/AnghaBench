#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvc0_graph_priv {int dummy; } ;
struct nvc0_graph_fuc {int /*<<< orphan*/ * data; int /*<<< orphan*/  size; } ;
struct nouveau_device {int chipset; TYPE_1__* pdev; } ;
struct firmware {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  f ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nouveau_device* nv_device (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nv_error (struct nvc0_graph_priv*,char*,char const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

int
nvc0_graph_ctor_fw(struct nvc0_graph_priv *priv, const char *fwname,
		   struct nvc0_graph_fuc *fuc)
{
	struct nouveau_device *device = nv_device(priv);
	const struct firmware *fw;
	char f[32];
	int ret;

	snprintf(f, sizeof(f), "nouveau/nv%02x_%s", device->chipset, fwname);
	ret = request_firmware(&fw, f, &device->pdev->dev);
	if (ret) {
		snprintf(f, sizeof(f), "nouveau/%s", fwname);
		ret = request_firmware(&fw, f, &device->pdev->dev);
		if (ret) {
			nv_error(priv, "failed to load %s\n", fwname);
			return ret;
		}
	}

	fuc->size = fw->size;
	fuc->data = kmemdup(fw->data, fuc->size, GFP_KERNEL);
	release_firmware(fw);
	return (fuc->data != NULL) ? 0 : -ENOMEM;
}