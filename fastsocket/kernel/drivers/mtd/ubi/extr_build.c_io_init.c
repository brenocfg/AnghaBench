#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubi_device {int vid_hdr_offset; int peb_size; int peb_count; int bad_allowed; int nor_flash; int min_io_size; int hdrs_min_io_size; int ec_hdr_alsize; int vid_hdr_alsize; int vid_hdr_aloffset; int vid_hdr_shift; int leb_start; int max_erroneous; int ro_mode; int leb_size; TYPE_1__* mtd; int /*<<< orphan*/  flash_size; } ;
struct TYPE_2__ {scalar_t__ numeraseregions; int erasesize; scalar_t__ type; int writesize; int subpage_sft; int flags; int index; scalar_t__ block_markbad; scalar_t__ block_isbad; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 void* ALIGN (int,int) ; 
 int EINVAL ; 
 scalar_t__ MTD_NORFLASH ; 
 int MTD_WRITEABLE ; 
 int UBI_EC_HDR_SIZE ; 
 int UBI_VID_HDR_SIZE ; 
 int /*<<< orphan*/  dbg_msg (char*,int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int mtd_div_by_eb (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_err (char*,...) ; 
 int /*<<< orphan*/  ubi_msg (char*,int,...) ; 
 int /*<<< orphan*/  ubi_warn (char*) ; 

__attribute__((used)) static int io_init(struct ubi_device *ubi)
{
	if (ubi->mtd->numeraseregions != 0) {
		/*
		 * Some flashes have several erase regions. Different regions
		 * may have different eraseblock size and other
		 * characteristics. It looks like mostly multi-region flashes
		 * have one "main" region and one or more small regions to
		 * store boot loader code or boot parameters or whatever. I
		 * guess we should just pick the largest region. But this is
		 * not implemented.
		 */
		ubi_err("multiple regions, not implemented");
		return -EINVAL;
	}

	if (ubi->vid_hdr_offset < 0)
		return -EINVAL;

	/*
	 * Note, in this implementation we support MTD devices with 0x7FFFFFFF
	 * physical eraseblocks maximum.
	 */

	ubi->peb_size   = ubi->mtd->erasesize;
	ubi->peb_count  = mtd_div_by_eb(ubi->mtd->size, ubi->mtd);
	ubi->flash_size = ubi->mtd->size;

	if (ubi->mtd->block_isbad && ubi->mtd->block_markbad)
		ubi->bad_allowed = 1;

	if (ubi->mtd->type == MTD_NORFLASH) {
		ubi_assert(ubi->mtd->writesize == 1);
		ubi->nor_flash = 1;
	}

	ubi->min_io_size = ubi->mtd->writesize;
	ubi->hdrs_min_io_size = ubi->mtd->writesize >> ubi->mtd->subpage_sft;

	/*
	 * Make sure minimal I/O unit is power of 2. Note, there is no
	 * fundamental reason for this assumption. It is just an optimization
	 * which allows us to avoid costly division operations.
	 */
	if (!is_power_of_2(ubi->min_io_size)) {
		ubi_err("min. I/O unit (%d) is not power of 2",
			ubi->min_io_size);
		return -EINVAL;
	}

	ubi_assert(ubi->hdrs_min_io_size > 0);
	ubi_assert(ubi->hdrs_min_io_size <= ubi->min_io_size);
	ubi_assert(ubi->min_io_size % ubi->hdrs_min_io_size == 0);

	/* Calculate default aligned sizes of EC and VID headers */
	ubi->ec_hdr_alsize = ALIGN(UBI_EC_HDR_SIZE, ubi->hdrs_min_io_size);
	ubi->vid_hdr_alsize = ALIGN(UBI_VID_HDR_SIZE, ubi->hdrs_min_io_size);

	dbg_msg("min_io_size      %d", ubi->min_io_size);
	dbg_msg("hdrs_min_io_size %d", ubi->hdrs_min_io_size);
	dbg_msg("ec_hdr_alsize    %d", ubi->ec_hdr_alsize);
	dbg_msg("vid_hdr_alsize   %d", ubi->vid_hdr_alsize);

	if (ubi->vid_hdr_offset == 0)
		/* Default offset */
		ubi->vid_hdr_offset = ubi->vid_hdr_aloffset =
				      ubi->ec_hdr_alsize;
	else {
		ubi->vid_hdr_aloffset = ubi->vid_hdr_offset &
						~(ubi->hdrs_min_io_size - 1);
		ubi->vid_hdr_shift = ubi->vid_hdr_offset -
						ubi->vid_hdr_aloffset;
	}

	/* Similar for the data offset */
	ubi->leb_start = ubi->vid_hdr_offset + UBI_EC_HDR_SIZE;
	ubi->leb_start = ALIGN(ubi->leb_start, ubi->min_io_size);

	dbg_msg("vid_hdr_offset   %d", ubi->vid_hdr_offset);
	dbg_msg("vid_hdr_aloffset %d", ubi->vid_hdr_aloffset);
	dbg_msg("vid_hdr_shift    %d", ubi->vid_hdr_shift);
	dbg_msg("leb_start        %d", ubi->leb_start);

	/* The shift must be aligned to 32-bit boundary */
	if (ubi->vid_hdr_shift % 4) {
		ubi_err("unaligned VID header shift %d",
			ubi->vid_hdr_shift);
		return -EINVAL;
	}

	/* Check sanity */
	if (ubi->vid_hdr_offset < UBI_EC_HDR_SIZE ||
	    ubi->leb_start < ubi->vid_hdr_offset + UBI_VID_HDR_SIZE ||
	    ubi->leb_start > ubi->peb_size - UBI_VID_HDR_SIZE ||
	    ubi->leb_start & (ubi->min_io_size - 1)) {
		ubi_err("bad VID header (%d) or data offsets (%d)",
			ubi->vid_hdr_offset, ubi->leb_start);
		return -EINVAL;
	}

	/*
	 * Set maximum amount of physical erroneous eraseblocks to be 10%.
	 * Erroneous PEB are those which have read errors.
	 */
	ubi->max_erroneous = ubi->peb_count / 10;
	if (ubi->max_erroneous < 16)
		ubi->max_erroneous = 16;
	dbg_msg("max_erroneous    %d", ubi->max_erroneous);

	/*
	 * It may happen that EC and VID headers are situated in one minimal
	 * I/O unit. In this case we can only accept this UBI image in
	 * read-only mode.
	 */
	if (ubi->vid_hdr_offset + UBI_VID_HDR_SIZE <= ubi->hdrs_min_io_size) {
		ubi_warn("EC and VID headers are in the same minimal I/O unit, "
			 "switch to read-only mode");
		ubi->ro_mode = 1;
	}

	ubi->leb_size = ubi->peb_size - ubi->leb_start;

	if (!(ubi->mtd->flags & MTD_WRITEABLE)) {
		ubi_msg("MTD device %d is write-protected, attach in "
			"read-only mode", ubi->mtd->index);
		ubi->ro_mode = 1;
	}

	ubi_msg("physical eraseblock size:   %d bytes (%d KiB)",
		ubi->peb_size, ubi->peb_size >> 10);
	ubi_msg("logical eraseblock size:    %d bytes", ubi->leb_size);
	ubi_msg("smallest flash I/O unit:    %d", ubi->min_io_size);
	if (ubi->hdrs_min_io_size != ubi->min_io_size)
		ubi_msg("sub-page size:              %d",
			ubi->hdrs_min_io_size);
	ubi_msg("VID header offset:          %d (aligned %d)",
		ubi->vid_hdr_offset, ubi->vid_hdr_aloffset);
	ubi_msg("data offset:                %d", ubi->leb_start);

	/*
	 * Note, ideally, we have to initialize ubi->bad_peb_count here. But
	 * unfortunately, MTD does not provide this information. We should loop
	 * over all physical eraseblocks and invoke mtd->block_is_bad() for
	 * each physical eraseblock. So, we skip ubi->bad_peb_count
	 * uninitialized and initialize it after scanning.
	 */

	return 0;
}