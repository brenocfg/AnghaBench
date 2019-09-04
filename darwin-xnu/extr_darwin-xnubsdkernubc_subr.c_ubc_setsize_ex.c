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
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ubc_setsize_opts_t ;
struct vnode {struct ubc_info* v_ubcinfo; } ;
struct ubc_info {scalar_t__ ui_size; int /*<<< orphan*/  ui_control; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  memory_object_size_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int MEMORY_OBJECT_DATA_FLUSH ; 
 int MEMORY_OBJECT_DATA_FLUSH_ALL ; 
 int /*<<< orphan*/  MEMORY_OBJECT_RETURN_NONE ; 
 int /*<<< orphan*/  NOTE_EXTEND ; 
 scalar_t__ PAGE_MASK_64 ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PAGE_SIZE_64 ; 
 int /*<<< orphan*/  UBCINFOEXISTS (struct vnode*) ; 
 int /*<<< orphan*/  UBC_SETSIZE_NO_FS_REENTRY ; 
 int /*<<< orphan*/  UPL_ABORT_FREE_ON_EMPTY ; 
 int /*<<< orphan*/  UPL_SET_LITE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int /*<<< orphan*/  VM_PROT_NO_CHANGE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_zero (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_vnode_and_post (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_to_bsd_errno (scalar_t__) ; 
 scalar_t__ memory_object_lock_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ round_page_64 (scalar_t__) ; 
 scalar_t__ trunc_page_64 (scalar_t__) ; 
 scalar_t__ ubc_create_upl_kernel (struct vnode*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_upl_abort_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ upl_valid_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

errno_t ubc_setsize_ex(struct vnode *vp, off_t nsize, ubc_setsize_opts_t opts)
{
	off_t osize;	/* ui_size before change */
	off_t lastpg, olastpgend, lastoff;
	struct ubc_info *uip;
	memory_object_control_t control;
	kern_return_t kret = KERN_SUCCESS;

	if (nsize < (off_t)0)
		return EINVAL;

	if (!UBCINFOEXISTS(vp))
		return ENOENT;

	uip = vp->v_ubcinfo;
	osize = uip->ui_size;

	if (ISSET(opts, UBC_SETSIZE_NO_FS_REENTRY) && nsize < osize)
		return EAGAIN;

	/*
	 * Update the size before flushing the VM
	 */
	uip->ui_size = nsize;

	if (nsize >= osize) {	/* Nothing more to do */
		if (nsize > osize) {
			lock_vnode_and_post(vp, NOTE_EXTEND);
		}

		return 0;
	}

	/*
	 * When the file shrinks, invalidate the pages beyond the
	 * new size. Also get rid of garbage beyond nsize on the
	 * last page. The ui_size already has the nsize, so any
	 * subsequent page-in will zero-fill the tail properly
	 */
	lastpg = trunc_page_64(nsize);
	olastpgend = round_page_64(osize);
	control = uip->ui_control;
	assert(control);
	lastoff = (nsize & PAGE_MASK_64);

	if (lastoff) {
		upl_t		upl;
		upl_page_info_t	*pl;

		/*
		 * new EOF ends up in the middle of a page
		 * zero the tail of this page if it's currently
		 * present in the cache
		 */
		kret = ubc_create_upl_kernel(vp, lastpg, PAGE_SIZE, &upl, &pl, UPL_SET_LITE, VM_KERN_MEMORY_FILE);

		if (kret != KERN_SUCCESS)
		        panic("ubc_setsize: ubc_create_upl (error = %d)\n", kret);

		if (upl_valid_page(pl, 0))
		        cluster_zero(upl, (uint32_t)lastoff, PAGE_SIZE - (uint32_t)lastoff, NULL);

		ubc_upl_abort_range(upl, 0, PAGE_SIZE, UPL_ABORT_FREE_ON_EMPTY);

		lastpg += PAGE_SIZE_64;
	}
	if (olastpgend > lastpg) {
		int	flags;

		if (lastpg == 0)
			flags = MEMORY_OBJECT_DATA_FLUSH_ALL;
		else
			flags = MEMORY_OBJECT_DATA_FLUSH;
		/*
		 * invalidate the pages beyond the new EOF page
		 *
		 */
		kret = memory_object_lock_request(control,
										  (memory_object_offset_t)lastpg,
										  (memory_object_size_t)(olastpgend - lastpg), NULL, NULL,
										  MEMORY_OBJECT_RETURN_NONE, flags, VM_PROT_NO_CHANGE);
		if (kret != KERN_SUCCESS)
		        printf("ubc_setsize: invalidate failed (error = %d)\n", kret);
	}
	return mach_to_bsd_errno(kret);
}