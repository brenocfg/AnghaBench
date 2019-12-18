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
typedef  int /*<<< orphan*/  uint16_t ;
struct nvbios {struct drm_device* dev; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;
struct bit_table {int (* parse_fn ) (struct drm_device*,struct nvbios*,struct bit_entry*) ;int /*<<< orphan*/  id; } ;
struct bit_entry {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ bit_table (struct drm_device*,int /*<<< orphan*/ ,struct bit_entry*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int stub1 (struct drm_device*,struct nvbios*,struct bit_entry*) ; 

__attribute__((used)) static int
parse_bit_table(struct nvbios *bios, const uint16_t bitoffset,
		struct bit_table *table)
{
	struct drm_device *dev = bios->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct bit_entry bitentry;

	if (bit_table(dev, table->id, &bitentry) == 0)
		return table->parse_fn(dev, bios, &bitentry);

	NV_INFO(drm, "BIT table '%c' not found\n", table->id);
	return -ENOSYS;
}