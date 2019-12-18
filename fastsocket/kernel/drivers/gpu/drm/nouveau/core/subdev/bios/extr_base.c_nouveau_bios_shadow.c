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
struct nouveau_bios {char* data; int /*<<< orphan*/  size; } ;
struct methods {char* member_0; int member_2; char* desc; int score; int rw; char* data; int /*<<< orphan*/  size; int /*<<< orphan*/  (* shadow ) (struct nouveau_bios*) ;int /*<<< orphan*/ * member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  cfgopt; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 int nouveau_bios_score (struct nouveau_bios*,int) ; 
 int /*<<< orphan*/  nouveau_bios_shadow_acpi ; 
 int /*<<< orphan*/  nouveau_bios_shadow_of ; 
 int /*<<< orphan*/  nouveau_bios_shadow_pci ; 
 int /*<<< orphan*/  nouveau_bios_shadow_pramin ; 
 int /*<<< orphan*/  nouveau_bios_shadow_prom ; 
 char* nouveau_stropt (int /*<<< orphan*/ ,char*,int*) ; 
 TYPE_2__* nv_device (struct nouveau_bios*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_bios*,char*,...) ; 
 int /*<<< orphan*/  nv_info (struct nouveau_bios*,char*,char*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bios*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_bios*) ; 

__attribute__((used)) static int
nouveau_bios_shadow(struct nouveau_bios *bios)
{
	struct methods shadow_methods[] = {
#if defined(__powerpc__)
		{ "OpenFirmware", nouveau_bios_shadow_of, true, 0, 0, NULL },
#endif
		{ "PRAMIN", nouveau_bios_shadow_pramin, true, 0, 0, NULL },
		{ "PROM", nouveau_bios_shadow_prom, false, 0, 0, NULL },
		{ "ACPI", nouveau_bios_shadow_acpi, true, 0, 0, NULL },
		{ "PCIROM", nouveau_bios_shadow_pci, true, 0, 0, NULL },
		{}
	};
	struct methods *mthd, *best;
	const struct firmware *fw;
	const char *optarg;
	int optlen, ret;
	char *source;

	optarg = nouveau_stropt(nv_device(bios)->cfgopt, "NvBios", &optlen);
	source = optarg ? kstrndup(optarg, optlen, GFP_KERNEL) : NULL;
	if (source) {
		/* try to match one of the built-in methods */
		mthd = shadow_methods;
		do {
			if (strcasecmp(source, mthd->desc))
				continue;
			nv_info(bios, "source: %s\n", mthd->desc);

			mthd->shadow(bios);
			mthd->score = nouveau_bios_score(bios, mthd->rw);
			if (mthd->score) {
				kfree(source);
				return 0;
			}
		} while ((++mthd)->shadow);

		/* attempt to load firmware image */
		ret = request_firmware(&fw, source, &nv_device(bios)->pdev->dev);
		if (ret == 0) {
			bios->size = fw->size;
			bios->data = kmemdup(fw->data, fw->size, GFP_KERNEL);
			release_firmware(fw);

			nv_info(bios, "image: %s\n", source);
			if (nouveau_bios_score(bios, 1)) {
				kfree(source);
				return 0;
			}

			kfree(bios->data);
			bios->data = NULL;
		}

		nv_error(bios, "source \'%s\' invalid\n", source);
		kfree(source);
	}

	mthd = shadow_methods;
	do {
		nv_info(bios, "checking %s for image...\n", mthd->desc);
		mthd->shadow(bios);
		mthd->score = nouveau_bios_score(bios, mthd->rw);
		mthd->size = bios->size;
		mthd->data = bios->data;
		bios->data = NULL;
	} while (mthd->score != 3 && (++mthd)->shadow);

	mthd = shadow_methods;
	best = mthd;
	do {
		if (mthd->score > best->score) {
			kfree(best->data);
			best = mthd;
		}
	} while ((++mthd)->shadow);

	if (best->score) {
		nv_info(bios, "using image from %s\n", best->desc);
		bios->size = best->size;
		bios->data = best->data;
		return 0;
	}

	nv_error(bios, "unable to locate usable image\n");
	return -EINVAL;
}