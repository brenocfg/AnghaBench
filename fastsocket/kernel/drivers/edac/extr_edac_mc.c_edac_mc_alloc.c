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
struct mem_ctl_info {int mc_idx; unsigned int nr_csrows; int csrow_idx; unsigned int nr_channels; int chan_idx; int /*<<< orphan*/  grp_kobj_list; int /*<<< orphan*/  op_state; struct mem_ctl_info* csrow; struct mem_ctl_info* channels; struct mem_ctl_info* mci; void* pvt_info; struct mem_ctl_info* csrows; } ;
struct csrow_info {int mc_idx; unsigned int nr_csrows; int csrow_idx; unsigned int nr_channels; int chan_idx; int /*<<< orphan*/  grp_kobj_list; int /*<<< orphan*/  op_state; struct csrow_info* csrow; struct csrow_info* channels; struct csrow_info* mci; void* pvt_info; struct csrow_info* csrows; } ;
struct channel_info {int mc_idx; unsigned int nr_csrows; int csrow_idx; unsigned int nr_channels; int chan_idx; int /*<<< orphan*/  grp_kobj_list; int /*<<< orphan*/  op_state; struct channel_info* csrow; struct channel_info* channels; struct channel_info* mci; void* pvt_info; struct channel_info* csrows; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OP_ALLOC ; 
 void* edac_align_ptr (struct mem_ctl_info*,unsigned int) ; 
 int edac_mc_register_sysfs_main_kobj (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  kfree (struct mem_ctl_info*) ; 
 struct mem_ctl_info* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 

struct mem_ctl_info *edac_mc_alloc(unsigned sz_pvt, unsigned nr_csrows,
				unsigned nr_chans, int edac_index)
{
	struct mem_ctl_info *mci;
	struct csrow_info *csi, *csrow;
	struct channel_info *chi, *chp, *chan;
	void *pvt;
	unsigned size;
	int row, chn;
	int err;

	/* Figure out the offsets of the various items from the start of an mc
	 * structure.  We want the alignment of each item to be at least as
	 * stringent as what the compiler would provide if we could simply
	 * hardcode everything into a single struct.
	 */
	mci = (struct mem_ctl_info *)0;
	csi = edac_align_ptr(&mci[1], sizeof(*csi));
	chi = edac_align_ptr(&csi[nr_csrows], sizeof(*chi));
	pvt = edac_align_ptr(&chi[nr_chans * nr_csrows], sz_pvt);
	size = ((unsigned long)pvt) + sz_pvt;

	mci = kzalloc(size, GFP_KERNEL);
	if (mci == NULL)
		return NULL;

	/* Adjust pointers so they point within the memory we just allocated
	 * rather than an imaginary chunk of memory located at address 0.
	 */
	csi = (struct csrow_info *)(((char *)mci) + ((unsigned long)csi));
	chi = (struct channel_info *)(((char *)mci) + ((unsigned long)chi));
	pvt = sz_pvt ? (((char *)mci) + ((unsigned long)pvt)) : NULL;

	/* setup index and various internal pointers */
	mci->mc_idx = edac_index;
	mci->csrows = csi;
	mci->pvt_info = pvt;
	mci->nr_csrows = nr_csrows;

	for (row = 0; row < nr_csrows; row++) {
		csrow = &csi[row];
		csrow->csrow_idx = row;
		csrow->mci = mci;
		csrow->nr_channels = nr_chans;
		chp = &chi[row * nr_chans];
		csrow->channels = chp;

		for (chn = 0; chn < nr_chans; chn++) {
			chan = &chp[chn];
			chan->chan_idx = chn;
			chan->csrow = csrow;
		}
	}

	mci->op_state = OP_ALLOC;
	INIT_LIST_HEAD(&mci->grp_kobj_list);

	/*
	 * Initialize the 'root' kobj for the edac_mc controller
	 */
	err = edac_mc_register_sysfs_main_kobj(mci);
	if (err) {
		kfree(mci);
		return NULL;
	}

	/* at this point, the root kobj is valid, and in order to
	 * 'free' the object, then the function:
	 *      edac_mc_unregister_sysfs_main_kobj() must be called
	 * which will perform kobj unregistration and the actual free
	 * will occur during the kobject callback operation
	 */
	return mci;
}