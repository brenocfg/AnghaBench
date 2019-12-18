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
struct ubi_vid_hdr {void* hdr_crc; int /*<<< orphan*/  version; void* magic; } ;
struct ubi_device {int peb_count; char* vid_hdr_shift; int /*<<< orphan*/  vid_hdr_alsize; int /*<<< orphan*/  vid_hdr_aloffset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int /*<<< orphan*/  UBI_VERSION ; 
 int /*<<< orphan*/  UBI_VID_HDR_MAGIC ; 
 int /*<<< orphan*/  UBI_VID_HDR_SIZE_CRC ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,struct ubi_vid_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_io (char*,int) ; 
 int paranoid_check_peb_ec_hdr (struct ubi_device*,int) ; 
 int paranoid_check_vid_hdr (struct ubi_device*,int,struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_io_write (struct ubi_device*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ubi_io_write_vid_hdr(struct ubi_device *ubi, int pnum,
			 struct ubi_vid_hdr *vid_hdr)
{
	int err;
	uint32_t crc;
	void *p;

	dbg_io("write VID header to PEB %d", pnum);
	ubi_assert(pnum >= 0 &&  pnum < ubi->peb_count);

	err = paranoid_check_peb_ec_hdr(ubi, pnum);
	if (err)
		return err > 0 ? -EINVAL : err;

	vid_hdr->magic = cpu_to_be32(UBI_VID_HDR_MAGIC);
	vid_hdr->version = UBI_VERSION;
	crc = crc32(UBI_CRC32_INIT, vid_hdr, UBI_VID_HDR_SIZE_CRC);
	vid_hdr->hdr_crc = cpu_to_be32(crc);

	err = paranoid_check_vid_hdr(ubi, pnum, vid_hdr);
	if (err)
		return -EINVAL;

	p = (char *)vid_hdr - ubi->vid_hdr_shift;
	err = ubi_io_write(ubi, p, pnum, ubi->vid_hdr_aloffset,
			   ubi->vid_hdr_alsize);
	return err;
}