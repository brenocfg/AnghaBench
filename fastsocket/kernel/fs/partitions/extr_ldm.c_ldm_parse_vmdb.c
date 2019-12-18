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
typedef  int /*<<< orphan*/  u8 ;
struct vmdb {int ver_major; int ver_minor; scalar_t__ last_vblk_seq; scalar_t__ vblk_offset; scalar_t__ vblk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MAGIC_VMDB ; 
 void* get_unaligned_be16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ get_unaligned_be32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldm_crit (char*) ; 
 int /*<<< orphan*/  ldm_debug (char*) ; 
 int /*<<< orphan*/  ldm_error (char*,int,int,int,int) ; 

__attribute__((used)) static bool ldm_parse_vmdb (const u8 *data, struct vmdb *vm)
{
	BUG_ON (!data || !vm);

	if (MAGIC_VMDB != get_unaligned_be32(data)) {
		ldm_crit ("Cannot find the VMDB, database may be corrupt.");
		return false;
	}

	vm->ver_major = get_unaligned_be16(data + 0x12);
	vm->ver_minor = get_unaligned_be16(data + 0x14);
	if ((vm->ver_major != 4) || (vm->ver_minor != 10)) {
		ldm_error ("Expected VMDB version %d.%d, got %d.%d. "
			"Aborting.", 4, 10, vm->ver_major, vm->ver_minor);
		return false;
	}

	vm->vblk_size     = get_unaligned_be32(data + 0x08);
	vm->vblk_offset   = get_unaligned_be32(data + 0x0C);
	vm->last_vblk_seq = get_unaligned_be32(data + 0x04);

	ldm_debug ("Parsed VMDB successfully.");
	return true;
}