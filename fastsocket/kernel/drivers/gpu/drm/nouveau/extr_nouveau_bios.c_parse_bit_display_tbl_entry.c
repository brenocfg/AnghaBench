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
struct TYPE_2__ {int /*<<< orphan*/  fptablepointer; } ;
struct nvbios {int /*<<< orphan*/ * data; TYPE_1__ fp; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int length; int offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  ROM16 (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static int parse_bit_display_tbl_entry(struct drm_device *dev, struct nvbios *bios, struct bit_entry *bitentry)
{
	/*
	 * Parses the flat panel table segment that the bit entry points to.
	 * Starting at bitentry->offset:
	 *
	 * offset + 0  (16 bits): ??? table pointer - seems to have 18 byte
	 * records beginning with a freq.
	 * offset + 2  (16 bits): mode table pointer
	 */
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (bitentry->length != 4) {
		NV_ERROR(drm, "Do not understand BIT display table\n");
		return -EINVAL;
	}

	bios->fp.fptablepointer = ROM16(bios->data[bitentry->offset + 2]);

	return 0;
}