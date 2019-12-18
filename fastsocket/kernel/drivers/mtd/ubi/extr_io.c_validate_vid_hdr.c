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
struct ubi_vid_hdr {int vol_type; int copy_flag; int compat; int /*<<< orphan*/  data_crc; int /*<<< orphan*/  data_pad; int /*<<< orphan*/  used_ebs; int /*<<< orphan*/  data_size; int /*<<< orphan*/  lnum; int /*<<< orphan*/  vol_id; } ;
struct ubi_device {int leb_size; } ;

/* Variables and functions */
 int UBI_COMPAT_DELETE ; 
 int UBI_COMPAT_PRESERVE ; 
 int UBI_COMPAT_REJECT ; 
 int UBI_COMPAT_RO ; 
 int UBI_INTERNAL_VOL_START ; 
 int UBI_MAX_VOLUMES ; 
 int UBI_VID_DYNAMIC ; 
 int UBI_VID_STATIC ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_err (char*) ; 
 int /*<<< orphan*/  ubi_dbg_dump_stack () ; 
 int /*<<< orphan*/  ubi_dbg_dump_vid_hdr (struct ubi_vid_hdr const*) ; 
 int /*<<< orphan*/  ubi_err (char*) ; 

__attribute__((used)) static int validate_vid_hdr(const struct ubi_device *ubi,
			    const struct ubi_vid_hdr *vid_hdr)
{
	int vol_type = vid_hdr->vol_type;
	int copy_flag = vid_hdr->copy_flag;
	int vol_id = be32_to_cpu(vid_hdr->vol_id);
	int lnum = be32_to_cpu(vid_hdr->lnum);
	int compat = vid_hdr->compat;
	int data_size = be32_to_cpu(vid_hdr->data_size);
	int used_ebs = be32_to_cpu(vid_hdr->used_ebs);
	int data_pad = be32_to_cpu(vid_hdr->data_pad);
	int data_crc = be32_to_cpu(vid_hdr->data_crc);
	int usable_leb_size = ubi->leb_size - data_pad;

	if (copy_flag != 0 && copy_flag != 1) {
		dbg_err("bad copy_flag");
		goto bad;
	}

	if (vol_id < 0 || lnum < 0 || data_size < 0 || used_ebs < 0 ||
	    data_pad < 0) {
		dbg_err("negative values");
		goto bad;
	}

	if (vol_id >= UBI_MAX_VOLUMES && vol_id < UBI_INTERNAL_VOL_START) {
		dbg_err("bad vol_id");
		goto bad;
	}

	if (vol_id < UBI_INTERNAL_VOL_START && compat != 0) {
		dbg_err("bad compat");
		goto bad;
	}

	if (vol_id >= UBI_INTERNAL_VOL_START && compat != UBI_COMPAT_DELETE &&
	    compat != UBI_COMPAT_RO && compat != UBI_COMPAT_PRESERVE &&
	    compat != UBI_COMPAT_REJECT) {
		dbg_err("bad compat");
		goto bad;
	}

	if (vol_type != UBI_VID_DYNAMIC && vol_type != UBI_VID_STATIC) {
		dbg_err("bad vol_type");
		goto bad;
	}

	if (data_pad >= ubi->leb_size / 2) {
		dbg_err("bad data_pad");
		goto bad;
	}

	if (vol_type == UBI_VID_STATIC) {
		/*
		 * Although from high-level point of view static volumes may
		 * contain zero bytes of data, but no VID headers can contain
		 * zero at these fields, because they empty volumes do not have
		 * mapped logical eraseblocks.
		 */
		if (used_ebs == 0) {
			dbg_err("zero used_ebs");
			goto bad;
		}
		if (data_size == 0) {
			dbg_err("zero data_size");
			goto bad;
		}
		if (lnum < used_ebs - 1) {
			if (data_size != usable_leb_size) {
				dbg_err("bad data_size");
				goto bad;
			}
		} else if (lnum == used_ebs - 1) {
			if (data_size == 0) {
				dbg_err("bad data_size at last LEB");
				goto bad;
			}
		} else {
			dbg_err("too high lnum");
			goto bad;
		}
	} else {
		if (copy_flag == 0) {
			if (data_crc != 0) {
				dbg_err("non-zero data CRC");
				goto bad;
			}
			if (data_size != 0) {
				dbg_err("non-zero data_size");
				goto bad;
			}
		} else {
			if (data_size == 0) {
				dbg_err("zero data_size of copy");
				goto bad;
			}
		}
		if (used_ebs != 0) {
			dbg_err("bad used_ebs");
			goto bad;
		}
	}

	return 0;

bad:
	ubi_err("bad VID header");
	ubi_dbg_dump_vid_hdr(vid_hdr);
	ubi_dbg_dump_stack();
	return 1;
}