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
struct ubi_volume {scalar_t__ reserved_pebs; scalar_t__ vol_type; scalar_t__ data_pad; } ;
struct ubi_scan_volume {scalar_t__ highest_lnum; scalar_t__ leb_count; scalar_t__ vol_type; scalar_t__ used_ebs; scalar_t__ data_pad; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ubi_dbg_dump_sv (struct ubi_scan_volume const*) ; 
 int /*<<< orphan*/  ubi_dbg_dump_vol_info (struct ubi_volume const*) ; 
 int /*<<< orphan*/  ubi_err (char*,int) ; 

__attribute__((used)) static int check_sv(const struct ubi_volume *vol,
		    const struct ubi_scan_volume *sv)
{
	int err;

	if (sv->highest_lnum >= vol->reserved_pebs) {
		err = 1;
		goto bad;
	}
	if (sv->leb_count > vol->reserved_pebs) {
		err = 2;
		goto bad;
	}
	if (sv->vol_type != vol->vol_type) {
		err = 3;
		goto bad;
	}
	if (sv->used_ebs > vol->reserved_pebs) {
		err = 4;
		goto bad;
	}
	if (sv->data_pad != vol->data_pad) {
		err = 5;
		goto bad;
	}
	return 0;

bad:
	ubi_err("bad scanning information, error %d", err);
	ubi_dbg_dump_sv(sv);
	ubi_dbg_dump_vol_info(vol);
	return -EINVAL;
}