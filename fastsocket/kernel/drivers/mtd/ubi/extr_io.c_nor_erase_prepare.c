#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct ubi_vid_hdr {int dummy; } ;
struct ubi_device {int peb_size; int vid_hdr_aloffset; TYPE_1__* mtd; } ;
typedef  int loff_t ;
struct TYPE_3__ {int (* write ) (TYPE_1__*,int,int,size_t*,void*) ;} ;

/* Variables and functions */
 int EIO ; 
 int UBI_IO_BAD_VID_HDR ; 
 int stub1 (TYPE_1__*,int,int,size_t*,void*) ; 
 int stub2 (TYPE_1__*,int,int,size_t*,void*) ; 
 int /*<<< orphan*/  ubi_dbg_dump_flash (struct ubi_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubi_err (char*,int,int,int) ; 
 int ubi_io_read_vid_hdr (struct ubi_device*,int,struct ubi_vid_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nor_erase_prepare(struct ubi_device *ubi, int pnum)
{
	int err, err1;
	size_t written;
	loff_t addr;
	uint32_t data = 0;
	struct ubi_vid_hdr vid_hdr;

	addr = (loff_t)pnum * ubi->peb_size + ubi->vid_hdr_aloffset;
	err = ubi->mtd->write(ubi->mtd, addr, 4, &written, (void *)&data);
	if (!err) {
		addr -= ubi->vid_hdr_aloffset;
		err = ubi->mtd->write(ubi->mtd, addr, 4, &written,
				      (void *)&data);
		if (!err)
			return 0;
	}

	/*
	 * We failed to write to the media. This was observed with Spansion
	 * S29GL512N NOR flash. Most probably the eraseblock erasure was
	 * interrupted at a very inappropriate moment, so it became unwritable.
	 * In this case we probably anyway have garbage in this PEB.
	 */
	err1 = ubi_io_read_vid_hdr(ubi, pnum, &vid_hdr, 0);
	if (err1 == UBI_IO_BAD_VID_HDR)
		/*
		 * The VID header is corrupted, so we can safely erase this
		 * PEB and not afraid that it will be treated as a valid PEB in
		 * case of an unclean reboot.
		 */
		return 0;

	/*
	 * The PEB contains a valid VID header, but we cannot invalidate it.
	 * Supposedly the flash media or the driver is screwed up, so return an
	 * error.
	 */
	ubi_err("cannot invalidate PEB %d, write returned %d read returned %d",
		pnum, err, err1);
	ubi_dbg_dump_flash(ubi, pnum, 0, ubi->peb_size);
	return -EIO;
}