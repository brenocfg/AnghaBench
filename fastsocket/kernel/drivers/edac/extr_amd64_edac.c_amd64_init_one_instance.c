#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {int /*<<< orphan*/  edac_cap; int /*<<< orphan*/ * dev; struct amd64_pvt* pvt_info; } ;
struct amd64_pvt {size_t mc_node_id; scalar_t__ channel_count; struct pci_dev* F2; TYPE_2__* csels; TYPE_1__* ops; } ;
struct amd64_family_type {int /*<<< orphan*/  f3_id; int /*<<< orphan*/  f1_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_cnt; } ;
struct TYPE_3__ {scalar_t__ (* early_channel_count ) (struct amd64_pvt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_FLAG_NONE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amd64_decode_bus_error ; 
 struct amd64_family_type* amd64_per_family_init (struct amd64_pvt*) ; 
 int /*<<< orphan*/  amd_register_ecc_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_report_gart_errors (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugf1 (char*) ; 
 int /*<<< orphan*/  drv_instances ; 
 scalar_t__ edac_mc_add_mc (struct mem_ctl_info*) ; 
 struct mem_ctl_info* edac_mc_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  free_mc_sibling_devs (struct amd64_pvt*) ; 
 size_t get_node_id (struct pci_dev*) ; 
 scalar_t__ init_csrows (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  kfree (struct amd64_pvt*) ; 
 struct amd64_pvt* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mem_ctl_info** mcis ; 
 int /*<<< orphan*/  read_mc_regs (struct amd64_pvt*) ; 
 scalar_t__ report_gart_errors ; 
 int reserve_mc_sibling_devs (struct amd64_pvt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mc_sysfs_attrs (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  setup_mci_misc_attrs (struct mem_ctl_info*,struct amd64_family_type*) ; 
 scalar_t__ stub1 (struct amd64_pvt*) ; 

__attribute__((used)) static int amd64_init_one_instance(struct pci_dev *F2)
{
	struct amd64_pvt *pvt = NULL;
	struct amd64_family_type *fam_type = NULL;
	struct mem_ctl_info *mci = NULL;
	int err = 0, ret;
	u8 nid = get_node_id(F2);

	ret = -ENOMEM;
	pvt = kzalloc(sizeof(struct amd64_pvt), GFP_KERNEL);
	if (!pvt)
		goto err_ret;

	pvt->mc_node_id	= nid;
	pvt->F2 = F2;

	ret = -EINVAL;
	fam_type = amd64_per_family_init(pvt);
	if (!fam_type)
		goto err_free;

	ret = -ENODEV;
	err = reserve_mc_sibling_devs(pvt, fam_type->f1_id, fam_type->f3_id);
	if (err)
		goto err_free;

	read_mc_regs(pvt);

	/*
	 * We need to determine how many memory channels there are. Then use
	 * that information for calculating the size of the dynamic instance
	 * tables in the 'mci' structure.
	 */
	ret = -EINVAL;
	pvt->channel_count = pvt->ops->early_channel_count(pvt);
	if (pvt->channel_count < 0)
		goto err_siblings;

	ret = -ENOMEM;
	mci = edac_mc_alloc(0, pvt->csels[0].b_cnt, pvt->channel_count, nid);
	if (!mci)
		goto err_siblings;

	mci->pvt_info = pvt;
	mci->dev = &pvt->F2->dev;

	setup_mci_misc_attrs(mci, fam_type);

	if (init_csrows(mci))
		mci->edac_cap = EDAC_FLAG_NONE;

	set_mc_sysfs_attrs(mci);

	ret = -ENODEV;
	if (edac_mc_add_mc(mci)) {
		debugf1("failed edac_mc_add_mc()\n");
		goto err_add_mc;
	}

	/* register stuff with EDAC MCE */
	if (report_gart_errors)
		amd_report_gart_errors(true);

	amd_register_ecc_decoder(amd64_decode_bus_error);

	mcis[nid] = mci;

	atomic_inc(&drv_instances);

	return 0;

err_add_mc:
	edac_mc_free(mci);

err_siblings:
	free_mc_sibling_devs(pvt);

err_free:
	kfree(pvt);

err_ret:
	return ret;
}