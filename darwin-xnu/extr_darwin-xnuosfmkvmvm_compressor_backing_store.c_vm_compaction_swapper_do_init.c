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
typedef  int /*<<< orphan*/  uint64_t ;
struct vnode {int dummy; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SWAPFILENAME_INDEX_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VM_PAGER_COMPRESSOR_WITH_SWAP ; 
 int compaction_swapper_inited ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  kfree (char*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 char* swapfilename ; 
 int vm_compressor_catchup_threshold_divisor ; 
 scalar_t__ vm_compressor_catchup_threshold_divisor_overridden ; 
 int vm_compressor_majorcompact_threshold_divisor ; 
 scalar_t__ vm_compressor_majorcompact_threshold_divisor_overridden ; 
 int vm_compressor_minorcompact_threshold_divisor ; 
 scalar_t__ vm_compressor_minorcompact_threshold_divisor_overridden ; 
 scalar_t__ vm_compressor_mode ; 
 int vm_compressor_unthrottle_threshold_divisor ; 
 scalar_t__ vm_compressor_unthrottle_threshold_divisor_overridden ; 
 int /*<<< orphan*/  vm_swap_data_lock ; 
 int /*<<< orphan*/  vm_swapfile_close (int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  vm_swapfile_open (char*,struct vnode**) ; 
 scalar_t__ vm_swappin_avail ; 
 int /*<<< orphan*/  vm_swappin_enabled ; 
 scalar_t__ vnode_getswappin_avail (struct vnode*) ; 
 scalar_t__ vnode_pager_isSSD (struct vnode*) ; 
 int /*<<< orphan*/  vnode_setswapmount (struct vnode*) ; 

void
vm_compaction_swapper_do_init(void)
{
	struct	vnode *vp;
	char	*pathname;
	int	namelen;

	if (compaction_swapper_inited)
		return;

	if (vm_compressor_mode != VM_PAGER_COMPRESSOR_WITH_SWAP) {
		compaction_swapper_inited = 1;
		return;
	}
	lck_mtx_lock(&vm_swap_data_lock);

	if ( !compaction_swapper_inited) {

		namelen = (int)strlen(swapfilename) + SWAPFILENAME_INDEX_LEN + 1;
		pathname = (char*)kalloc(namelen);
		memset(pathname, 0, namelen);
		snprintf(pathname, namelen, "%s%d", swapfilename, 0);

		vm_swapfile_open(pathname, &vp);

		if (vp) {
			
			if (vnode_pager_isSSD(vp) == FALSE) {
			        /*
				 * swap files live on an HDD, so let's make sure to start swapping
				 * much earlier since we're not worried about SSD write-wear and 
				 * we have so little write bandwidth to work with
				 * these values were derived expermentially by running the performance
				 * teams stock test for evaluating HDD performance against various 
				 * combinations and looking and comparing overall results.
				 * Note that the > relationship between these 4 values must be maintained
				 */
			        if (vm_compressor_minorcompact_threshold_divisor_overridden == 0)
				        vm_compressor_minorcompact_threshold_divisor = 15;
			        if (vm_compressor_majorcompact_threshold_divisor_overridden == 0)
				        vm_compressor_majorcompact_threshold_divisor = 18;
			        if (vm_compressor_unthrottle_threshold_divisor_overridden == 0)
				        vm_compressor_unthrottle_threshold_divisor = 24;
				if (vm_compressor_catchup_threshold_divisor_overridden == 0)
				        vm_compressor_catchup_threshold_divisor = 30;
			}
#if !CONFIG_EMBEDDED
			vnode_setswapmount(vp);
			vm_swappin_avail = vnode_getswappin_avail(vp);

			if (vm_swappin_avail)
				vm_swappin_enabled = TRUE;
#endif
			vm_swapfile_close((uint64_t)pathname, vp);
		}
		kfree(pathname, namelen);

		compaction_swapper_inited = 1;
	}
	lck_mtx_unlock(&vm_swap_data_lock);
}