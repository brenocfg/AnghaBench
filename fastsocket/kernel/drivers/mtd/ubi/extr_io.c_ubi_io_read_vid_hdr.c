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
typedef  scalar_t__ uint32_t ;
struct ubi_vid_hdr {int /*<<< orphan*/  hdr_crc; int /*<<< orphan*/  magic; } ;
struct ubi_device {int peb_count; char* vid_hdr_shift; int /*<<< orphan*/  vid_hdr_alsize; int /*<<< orphan*/  vid_hdr_aloffset; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int UBI_IO_BAD_VID_HDR ; 
 int UBI_IO_BITFLIPS ; 
 scalar_t__ UBI_IO_DEBUG ; 
 int UBI_IO_PEB_FREE ; 
 scalar_t__ UBI_VID_HDR_MAGIC ; 
 int /*<<< orphan*/  UBI_VID_HDR_SIZE ; 
 int /*<<< orphan*/  UBI_VID_HDR_SIZE_CRC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ check_pattern (struct ubi_vid_hdr*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,struct ubi_vid_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_io (char*,int) ; 
 int /*<<< orphan*/  dbg_msg (char*,int,...) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_dbg_dump_vid_hdr (struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_err (char*,int) ; 
 int ubi_io_read (struct ubi_device*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_warn (char*,int,...) ; 
 int validate_vid_hdr (struct ubi_device*,struct ubi_vid_hdr*) ; 

int ubi_io_read_vid_hdr(struct ubi_device *ubi, int pnum,
			struct ubi_vid_hdr *vid_hdr, int verbose)
{
	int err, read_err = 0;
	uint32_t crc, magic, hdr_crc;
	void *p;

	dbg_io("read VID header from PEB %d", pnum);
	ubi_assert(pnum >= 0 &&  pnum < ubi->peb_count);

	p = (char *)vid_hdr - ubi->vid_hdr_shift;
	err = ubi_io_read(ubi, p, pnum, ubi->vid_hdr_aloffset,
			  ubi->vid_hdr_alsize);
	if (err) {
		if (err != UBI_IO_BITFLIPS && err != -EBADMSG)
			return err;

		/*
		 * We read all the data, but either a correctable bit-flip
		 * occurred, or MTD reported about some data integrity error,
		 * like an ECC error in case of NAND. The former is harmless,
		 * the later may mean the read data is corrupted. But we have a
		 * CRC check-sum and we will identify this. If the VID header is
		 * still OK, we just report this as there was a bit-flip.
		 */
		read_err = err;
	}

	magic = be32_to_cpu(vid_hdr->magic);
	if (magic != UBI_VID_HDR_MAGIC) {
		/*
		 * If we have read all 0xFF bytes, the VID header probably does
		 * not exist and the physical eraseblock is assumed to be free.
		 *
		 * But if there was a read error, we do not test the data for
		 * 0xFFs. Even if it does contain all 0xFFs, this error
		 * indicates that something is still wrong with this physical
		 * eraseblock and it cannot be regarded as free.
		 */
		if (read_err != -EBADMSG &&
		    check_pattern(vid_hdr, 0xFF, UBI_VID_HDR_SIZE)) {
			/* The physical eraseblock is supposedly free */
			if (verbose)
				ubi_warn("no VID header found at PEB %d, "
					 "only 0xFF bytes", pnum);
			else if (UBI_IO_DEBUG)
				dbg_msg("no VID header found at PEB %d, "
					"only 0xFF bytes", pnum);
			return UBI_IO_PEB_FREE;
		}

		/*
		 * This is not a valid VID header, and these are not 0xFF
		 * bytes. Report that the header is corrupted.
		 */
		if (verbose) {
			ubi_warn("bad magic number at PEB %d: %08x instead of "
				 "%08x", pnum, magic, UBI_VID_HDR_MAGIC);
			ubi_dbg_dump_vid_hdr(vid_hdr);
		} else if (UBI_IO_DEBUG)
			dbg_msg("bad magic number at PEB %d: %08x instead of "
				"%08x", pnum, magic, UBI_VID_HDR_MAGIC);
		return UBI_IO_BAD_VID_HDR;
	}

	crc = crc32(UBI_CRC32_INIT, vid_hdr, UBI_VID_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(vid_hdr->hdr_crc);

	if (hdr_crc != crc) {
		if (verbose) {
			ubi_warn("bad CRC at PEB %d, calculated %#08x, "
				 "read %#08x", pnum, crc, hdr_crc);
			ubi_dbg_dump_vid_hdr(vid_hdr);
		} else if (UBI_IO_DEBUG)
			dbg_msg("bad CRC at PEB %d, calculated %#08x, "
				"read %#08x", pnum, crc, hdr_crc);
		return UBI_IO_BAD_VID_HDR;
	}

	/* Validate the VID header that we have just read */
	err = validate_vid_hdr(ubi, vid_hdr);
	if (err) {
		ubi_err("validation failed for PEB %d", pnum);
		return -EINVAL;
	}

	return read_err ? UBI_IO_BITFLIPS : 0;
}