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
struct ubi_scan_info {int /*<<< orphan*/  mean_ec; int /*<<< orphan*/  max_ec; scalar_t__ bad_peb_count; } ;
struct ubi_device {int /*<<< orphan*/  vtbl; int /*<<< orphan*/  mean_ec; int /*<<< orphan*/  max_ec; scalar_t__ bad_peb_count; scalar_t__ peb_count; scalar_t__ good_peb_count; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubi_scan_info*) ; 
 int PTR_ERR (struct ubi_scan_info*) ; 
 int /*<<< orphan*/  free_internal_volumes (struct ubi_device*) ; 
 int ubi_eba_init_scan (struct ubi_device*,struct ubi_scan_info*) ; 
 int ubi_read_volume_table (struct ubi_device*,struct ubi_scan_info*) ; 
 struct ubi_scan_info* ubi_scan (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_scan_destroy_si (struct ubi_scan_info*) ; 
 int /*<<< orphan*/  ubi_wl_close (struct ubi_device*) ; 
 int ubi_wl_init_scan (struct ubi_device*,struct ubi_scan_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int attach_by_scanning(struct ubi_device *ubi)
{
	int err;
	struct ubi_scan_info *si;

	si = ubi_scan(ubi);
	if (IS_ERR(si))
		return PTR_ERR(si);

	ubi->bad_peb_count = si->bad_peb_count;
	ubi->good_peb_count = ubi->peb_count - ubi->bad_peb_count;
	ubi->max_ec = si->max_ec;
	ubi->mean_ec = si->mean_ec;

	err = ubi_read_volume_table(ubi, si);
	if (err)
		goto out_si;

	err = ubi_wl_init_scan(ubi, si);
	if (err)
		goto out_vtbl;

	err = ubi_eba_init_scan(ubi, si);
	if (err)
		goto out_wl;

	ubi_scan_destroy_si(si);
	return 0;

out_wl:
	ubi_wl_close(ubi);
out_vtbl:
	free_internal_volumes(ubi);
	vfree(ubi->vtbl);
out_si:
	ubi_scan_destroy_si(si);
	return err;
}