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
typedef  int /*<<< orphan*/  uint32_t ;
struct ubi_vtbl_record {int /*<<< orphan*/  crc; } ;
struct ubi_volume {int dummy; } ;
struct ubi_device {int vtbl_slots; int /*<<< orphan*/  vtbl_size; int /*<<< orphan*/ * vtbl; struct ubi_volume** volumes; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int UBI_LAYOUT_VOLUME_EBS ; 
 int /*<<< orphan*/  UBI_LAYOUT_VOLUME_ID ; 
 int /*<<< orphan*/  UBI_LONGTERM ; 
 int /*<<< orphan*/  UBI_VTBL_RECORD_SIZE_CRC ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,struct ubi_vtbl_record*,int /*<<< orphan*/ ) ; 
 struct ubi_vtbl_record empty_vtbl_record ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ubi_vtbl_record*,int) ; 
 int /*<<< orphan*/  paranoid_vtbl_check (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_eba_unmap_leb (struct ubi_device*,struct ubi_volume*,int) ; 
 int ubi_eba_write_leb (struct ubi_device*,struct ubi_volume*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t vol_id2idx (struct ubi_device*,int /*<<< orphan*/ ) ; 

int ubi_change_vtbl_record(struct ubi_device *ubi, int idx,
			   struct ubi_vtbl_record *vtbl_rec)
{
	int i, err;
	uint32_t crc;
	struct ubi_volume *layout_vol;

	ubi_assert(idx >= 0 && idx < ubi->vtbl_slots);
	layout_vol = ubi->volumes[vol_id2idx(ubi, UBI_LAYOUT_VOLUME_ID)];

	if (!vtbl_rec)
		vtbl_rec = &empty_vtbl_record;
	else {
		crc = crc32(UBI_CRC32_INIT, vtbl_rec, UBI_VTBL_RECORD_SIZE_CRC);
		vtbl_rec->crc = cpu_to_be32(crc);
	}

	memcpy(&ubi->vtbl[idx], vtbl_rec, sizeof(struct ubi_vtbl_record));
	for (i = 0; i < UBI_LAYOUT_VOLUME_EBS; i++) {
		err = ubi_eba_unmap_leb(ubi, layout_vol, i);
		if (err)
			return err;

		err = ubi_eba_write_leb(ubi, layout_vol, i, ubi->vtbl, 0,
					ubi->vtbl_size, UBI_LONGTERM);
		if (err)
			return err;
	}

	paranoid_vtbl_check(ubi);
	return 0;
}