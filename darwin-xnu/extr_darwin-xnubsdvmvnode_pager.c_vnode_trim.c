#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct vnode {TYPE_1__* v_mount; } ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {int offset; size_t length; int extentsCount; struct TYPE_6__* extents; } ;
typedef  TYPE_2__ dk_unmap_t ;
typedef  TYPE_2__ dk_extent_t ;
typedef  scalar_t__ daddr64_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {struct vnode* mnt_devvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DKIOCGETBLOCKSIZE ; 
 int /*<<< orphan*/  DKIOCUNMAP ; 
 int VNODE_BLOCKMAP_NO_TRACK ; 
 int VNODE_READ ; 
 int VNOP_BLOCKMAP (struct vnode*,scalar_t__,size_t,scalar_t__*,size_t*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int VNOP_IOCTL (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 

u_int32_t vnode_trim (
		struct vnode *vp,
		off_t offset,
		size_t length)
{
	daddr64_t io_blockno;	 /* Block number corresponding to the start of the extent */
	size_t io_bytecount;	/* Number of bytes in current extent for the specified range */
	size_t trimmed = 0;
	off_t current_offset = offset; 
	size_t remaining_length = length;
	int error = 0;
	u_int32_t blocksize = 0;
	struct vnode *devvp;
	dk_extent_t extent;
	dk_unmap_t unmap;


	/* Get the underlying device vnode */
	devvp = vp->v_mount->mnt_devvp;

	/* Figure out the underlying device block size */
	error  = VNOP_IOCTL(devvp, DKIOCGETBLOCKSIZE, (caddr_t)&blocksize, 0, vfs_context_kernel());
	if (error) {
		goto trim_exit;
	}

	/* 
	 * We may not get the entire range from offset -> offset+length in a single
	 * extent from the blockmap call.  Keep looping/going until we are sure we've hit
	 * the whole range or if we encounter an error.
	 */
	while (trimmed < length) {
		/*
		 * VNOP_BLOCKMAP will tell us the logical to physical block number mapping for the
		 * specified offset.  It returns blocks in contiguous chunks, so if the logical range is 
		 * broken into multiple extents, it must be called multiple times, increasing the offset
		 * in each call to ensure that the entire range is covered.
		 */
		error = VNOP_BLOCKMAP (vp, current_offset, remaining_length, 
				&io_blockno, &io_bytecount, NULL, VNODE_READ | VNODE_BLOCKMAP_NO_TRACK, NULL);

		if (error) {
			goto trim_exit;
		}
		/* 
		 * We have a contiguous run.  Prepare & issue the ioctl for the device.
		 * the DKIOCUNMAP ioctl takes offset in bytes from the start of the device.
		 */
		memset (&extent, 0, sizeof(dk_extent_t));
		memset (&unmap, 0, sizeof(dk_unmap_t));
		extent.offset = (uint64_t) io_blockno * (u_int64_t) blocksize;
		extent.length = io_bytecount;
		unmap.extents = &extent;
		unmap.extentsCount = 1;
		error = VNOP_IOCTL(devvp, DKIOCUNMAP, (caddr_t)&unmap, 0, vfs_context_kernel());

		if (error) {
			goto trim_exit;
		}
		remaining_length = remaining_length - io_bytecount;
		trimmed = trimmed + io_bytecount;
		current_offset = current_offset + io_bytecount;
	}
trim_exit:

	return error;

}