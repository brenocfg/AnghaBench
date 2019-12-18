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
typedef  char uint8_t ;
struct nvbios {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  hwsq_signature ;

/* Variables and functions */
 int findstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int const) ; 
 int load_nv17_hwsq_ucode_entry (struct drm_device*,struct nvbios*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_nv17_hw_sequencer_ucode(struct drm_device *dev,
					struct nvbios *bios)
{
	/*
	 * BMP based cards, from NV17, need a microcode loading to correctly
	 * control the GPIO etc for LVDS panels
	 *
	 * BIT based cards seem to do this directly in the init scripts
	 *
	 * The microcode entries are found by the "HWSQ" signature.
	 */

	const uint8_t hwsq_signature[] = { 'H', 'W', 'S', 'Q' };
	const int sz = sizeof(hwsq_signature);
	int hwsq_offset;

	hwsq_offset = findstr(bios->data, bios->length, hwsq_signature, sz);
	if (!hwsq_offset)
		return 0;

	/* always use entry 0? */
	return load_nv17_hwsq_ucode_entry(dev, bios, hwsq_offset + sz, 0);
}