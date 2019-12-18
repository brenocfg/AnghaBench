#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int uint64_t ;
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct vnode {int dummy; } ;
struct trim_list {size_t tl_offset; size_t tl_length; struct trim_list* tl_next; } ;
typedef  size_t off_t ;
struct TYPE_13__ {int extentsCount; TYPE_4__* extents; int /*<<< orphan*/  options; } ;
typedef  TYPE_3__ dk_unmap_t ;
struct TYPE_14__ {int offset; size_t length; } ;
typedef  TYPE_4__ dk_extent_t ;
typedef  int daddr64_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  scalar_t__ boolean_t ;
typedef  TYPE_3__ _dk_cs_unmap_t ;
struct TYPE_12__ {TYPE_1__* v_mount; } ;
struct TYPE_11__ {int mnt_ioflags; int mnt_devblocksize; struct vnode* mnt_devvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DKIOCUNMAP ; 
 int ENOTSUP ; 
 int MAX_BATCH_TO_TRIM ; 
 int MNT_IOFLAGS_CSUNMAP_SUPPORTED ; 
 int MNT_IOFLAGS_UNMAP_SUPPORTED ; 
 int /*<<< orphan*/  ROUTE_ONLY ; 
 scalar_t__ TRUE ; 
 int VNODE_BLOCKMAP_NO_TRACK ; 
 int VNODE_READ ; 
 int VNOP_BLOCKMAP (TYPE_2__*,size_t,size_t,int*,size_t*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int VNOP_IOCTL (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _DKIOCCSUNMAP ; 
 TYPE_4__* kalloc (int) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 

u_int32_t vnode_trim_list (vnode_t vp, struct trim_list *tl, boolean_t route_only)
{
	int		error = 0;
	int		trim_index = 0;
	u_int32_t	blocksize = 0;
	struct vnode	*devvp;
	dk_extent_t	*extents;
	dk_unmap_t	unmap;
	_dk_cs_unmap_t	cs_unmap;

	if ( !(vp->v_mount->mnt_ioflags & MNT_IOFLAGS_UNMAP_SUPPORTED))
		return (ENOTSUP);

	if (tl == NULL)
		return (0);

	/*
	 * Get the underlying device vnode and physical block size
	 */
	devvp = vp->v_mount->mnt_devvp;
	blocksize = vp->v_mount->mnt_devblocksize;

	extents = kalloc(sizeof(dk_extent_t) * MAX_BATCH_TO_TRIM);

	if (vp->v_mount->mnt_ioflags & MNT_IOFLAGS_CSUNMAP_SUPPORTED) {
		memset (&cs_unmap, 0, sizeof(_dk_cs_unmap_t));
		cs_unmap.extents = extents;

		if (route_only == TRUE)
			cs_unmap.options = ROUTE_ONLY;
	} else {
		memset (&unmap, 0, sizeof(dk_unmap_t));
		unmap.extents = extents;
	}

	while (tl) {
		daddr64_t	io_blockno;	/* Block number corresponding to the start of the extent */
		size_t		io_bytecount;	/* Number of bytes in current extent for the specified range */
		size_t		trimmed;
		size_t		remaining_length;
		off_t		current_offset; 

		current_offset = tl->tl_offset;
		remaining_length = tl->tl_length;
		trimmed = 0;
		
		/* 
		 * We may not get the entire range from tl_offset -> tl_offset+tl_length in a single
		 * extent from the blockmap call.  Keep looping/going until we are sure we've hit
		 * the whole range or if we encounter an error.
		 */
		while (trimmed < tl->tl_length) {
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
			if (io_blockno != -1) {
			        extents[trim_index].offset = (uint64_t) io_blockno * (u_int64_t) blocksize;
				extents[trim_index].length = io_bytecount;

				trim_index++;
			}
			if (trim_index == MAX_BATCH_TO_TRIM) {

				if (vp->v_mount->mnt_ioflags & MNT_IOFLAGS_CSUNMAP_SUPPORTED) {
					cs_unmap.extentsCount = trim_index;
					error = VNOP_IOCTL(devvp, _DKIOCCSUNMAP, (caddr_t)&cs_unmap, 0, vfs_context_kernel());
				} else {
					unmap.extentsCount = trim_index;
					error = VNOP_IOCTL(devvp, DKIOCUNMAP, (caddr_t)&unmap, 0, vfs_context_kernel());
				}
				if (error) {
					goto trim_exit;
				}
				trim_index = 0;
			}
			trimmed += io_bytecount;
			current_offset += io_bytecount;
			remaining_length -= io_bytecount;
		}
		tl = tl->tl_next;
	}
	if (trim_index) {
		if (vp->v_mount->mnt_ioflags & MNT_IOFLAGS_CSUNMAP_SUPPORTED) {
			cs_unmap.extentsCount = trim_index;
			error = VNOP_IOCTL(devvp, _DKIOCCSUNMAP, (caddr_t)&cs_unmap, 0, vfs_context_kernel());
		} else {
			unmap.extentsCount = trim_index;
			error = VNOP_IOCTL(devvp, DKIOCUNMAP, (caddr_t)&unmap, 0, vfs_context_kernel());
		}
	}
trim_exit:
	kfree(extents, sizeof(dk_extent_t) * MAX_BATCH_TO_TRIM);

	return error;
}