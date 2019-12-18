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
struct nvbios {int /*<<< orphan*/ * data; void* ram_restrict_tbl_ptr; int /*<<< orphan*/  ram_restrict_group_count; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int length; int version; int offset; } ;

/* Variables and functions */
 void* ROM16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_bit_M_tbl_entry(struct drm_device *dev, struct nvbios *bios,
		      struct bit_entry *bitentry)
{
	/*
	 * offset + 2  (8  bits): number of options in an
	 * 	INIT_RAM_RESTRICT_ZM_REG_GROUP opcode option set
	 * offset + 3  (16 bits): pointer to strap xlate table for RAM
	 * 	restrict option selection
	 *
	 * There's a bunch of bits in this table other than the RAM restrict
	 * stuff that we don't use - their use currently unknown
	 */

	/*
	 * Older bios versions don't have a sufficiently long table for
	 * what we want
	 */
	if (bitentry->length < 0x5)
		return 0;

	if (bitentry->version < 2) {
		bios->ram_restrict_group_count = bios->data[bitentry->offset + 2];
		bios->ram_restrict_tbl_ptr = ROM16(bios->data[bitentry->offset + 3]);
	} else {
		bios->ram_restrict_group_count = bios->data[bitentry->offset + 0];
		bios->ram_restrict_tbl_ptr = ROM16(bios->data[bitentry->offset + 1]);
	}

	return 0;
}