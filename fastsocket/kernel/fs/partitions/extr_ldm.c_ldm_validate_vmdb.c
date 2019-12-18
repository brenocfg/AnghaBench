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
struct vmdb {int vblk_offset; int vblk_size; int last_vblk_seq; } ;
struct tocblock {int bitmap1_size; } ;
struct ldmdb {struct tocblock toc; struct vmdb vm; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OFF_VMDB ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldm_crit (char*) ; 
 int /*<<< orphan*/  ldm_info (char*,int) ; 
 int /*<<< orphan*/  ldm_parse_vmdb (int /*<<< orphan*/ *,struct vmdb*) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_dev_sector (struct block_device*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ldm_validate_vmdb (struct block_device *bdev, unsigned long base,
			       struct ldmdb *ldb)
{
	Sector sect;
	u8 *data;
	bool result = false;
	struct vmdb *vm;
	struct tocblock *toc;

	BUG_ON (!bdev || !ldb);

	vm  = &ldb->vm;
	toc = &ldb->toc;

	data = read_dev_sector (bdev, base + OFF_VMDB, &sect);
	if (!data) {
		ldm_crit ("Disk read failed.");
		return false;
	}

	if (!ldm_parse_vmdb (data, vm))
		goto out;				/* Already logged */

	/* Are there uncommitted transactions? */
	if (get_unaligned_be16(data + 0x10) != 0x01) {
		ldm_crit ("Database is not in a consistent state.  Aborting.");
		goto out;
	}

	if (vm->vblk_offset != 512)
		ldm_info ("VBLKs start at offset 0x%04x.", vm->vblk_offset);

	/*
	 * The last_vblkd_seq can be before the end of the vmdb, just make sure
	 * it is not out of bounds.
	 */
	if ((vm->vblk_size * vm->last_vblk_seq) > (toc->bitmap1_size << 9)) {
		ldm_crit ("VMDB exceeds allowed size specified by TOCBLOCK.  "
				"Database is corrupt.  Aborting.");
		goto out;
	}

	result = true;
out:
	put_dev_sector (sect);
	return result;
}