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
struct nvbios {int major_version; int* data; } ;
struct nouveau_device {scalar_t__ card_type; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int NVReadVgaCrtc5758 (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NV_50 ; 
 int /*<<< orphan*/  NV_PEXTDEV_BOOT_0 ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int nv_rd32 (struct nouveau_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_fp_strap(struct drm_device *dev, struct nvbios *bios)
{
	struct nouveau_device *device = nouveau_dev(dev);

	/*
	 * The fp strap is normally dictated by the "User Strap" in
	 * PEXTDEV_BOOT_0[20:16], but on BMP cards when bit 2 of the
	 * Internal_Flags struct at 0x48 is set, the user strap gets overriden
	 * by the PCI subsystem ID during POST, but not before the previous user
	 * strap has been committed to CR58 for CR57=0xf on head A, which may be
	 * read and used instead
	 */

	if (bios->major_version < 5 && bios->data[0x48] & 0x4)
		return NVReadVgaCrtc5758(dev, 0, 0xf) & 0xf;

	if (device->card_type >= NV_50)
		return (nv_rd32(device, NV_PEXTDEV_BOOT_0) >> 24) & 0xf;
	else
		return (nv_rd32(device, NV_PEXTDEV_BOOT_0) >> 16) & 0xf;
}