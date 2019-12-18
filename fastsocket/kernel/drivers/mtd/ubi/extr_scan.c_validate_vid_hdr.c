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
struct ubi_vid_hdr {int vol_type; int /*<<< orphan*/  data_pad; int /*<<< orphan*/  used_ebs; int /*<<< orphan*/  vol_id; } ;
struct ubi_scan_volume {scalar_t__ leb_count; int vol_id; scalar_t__ vol_type; int used_ebs; int data_pad; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UBI_STATIC_VOLUME ; 
 int UBI_VID_DYNAMIC ; 
 int UBI_VID_STATIC ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_err (char*) ; 
 int /*<<< orphan*/  ubi_dbg_dump_sv (struct ubi_scan_volume const*) ; 
 int /*<<< orphan*/  ubi_dbg_dump_vid_hdr (struct ubi_vid_hdr const*) ; 
 int /*<<< orphan*/  ubi_err (char*,int) ; 

__attribute__((used)) static int validate_vid_hdr(const struct ubi_vid_hdr *vid_hdr,
			    const struct ubi_scan_volume *sv, int pnum)
{
	int vol_type = vid_hdr->vol_type;
	int vol_id = be32_to_cpu(vid_hdr->vol_id);
	int used_ebs = be32_to_cpu(vid_hdr->used_ebs);
	int data_pad = be32_to_cpu(vid_hdr->data_pad);

	if (sv->leb_count != 0) {
		int sv_vol_type;

		/*
		 * This is not the first logical eraseblock belonging to this
		 * volume. Ensure that the data in its VID header is consistent
		 * to the data in previous logical eraseblock headers.
		 */

		if (vol_id != sv->vol_id) {
			dbg_err("inconsistent vol_id");
			goto bad;
		}

		if (sv->vol_type == UBI_STATIC_VOLUME)
			sv_vol_type = UBI_VID_STATIC;
		else
			sv_vol_type = UBI_VID_DYNAMIC;

		if (vol_type != sv_vol_type) {
			dbg_err("inconsistent vol_type");
			goto bad;
		}

		if (used_ebs != sv->used_ebs) {
			dbg_err("inconsistent used_ebs");
			goto bad;
		}

		if (data_pad != sv->data_pad) {
			dbg_err("inconsistent data_pad");
			goto bad;
		}
	}

	return 0;

bad:
	ubi_err("inconsistent VID header at PEB %d", pnum);
	ubi_dbg_dump_vid_hdr(vid_hdr);
	ubi_dbg_dump_sv(sv);
	return -EINVAL;
}