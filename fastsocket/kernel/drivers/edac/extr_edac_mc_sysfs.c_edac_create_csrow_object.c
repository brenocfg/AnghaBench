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
struct kobject {int dummy; } ;
struct mem_ctl_info {struct kobject edac_mci_kobj; } ;
struct csrow_info {int nr_channels; struct kobject kobj; struct mem_ctl_info* mci; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int edac_create_channel_files (struct kobject*,int) ; 
 struct kobject* kobject_get (struct kobject*) ; 
 int kobject_init_and_add (struct kobject*,int /*<<< orphan*/ *,struct kobject*,char*,int) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  kobject_uevent (struct kobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_csrow ; 
 int /*<<< orphan*/  memset (struct kobject*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int edac_create_csrow_object(struct mem_ctl_info *mci,
					struct csrow_info *csrow, int index)
{
	struct kobject *kobj_mci = &mci->edac_mci_kobj;
	struct kobject *kobj;
	int chan;
	int err;

	/* generate ..../edac/mc/mc<id>/csrow<index>   */
	memset(&csrow->kobj, 0, sizeof(csrow->kobj));
	csrow->mci = mci;	/* include container up link */

	/* bump the mci instance's kobject's ref count */
	kobj = kobject_get(&mci->edac_mci_kobj);
	if (!kobj) {
		err = -ENODEV;
		goto err_out;
	}

	/* Instanstiate the csrow object */
	err = kobject_init_and_add(&csrow->kobj, &ktype_csrow, kobj_mci,
				   "csrow%d", index);
	if (err)
		goto err_release_top_kobj;

	/* At this point, to release a csrow kobj, one must
	 * call the kobject_put and allow that tear down
	 * to work the releasing
	 */

	/* Create the dyanmic attribute files on this csrow,
	 * namely, the DIMM labels and the channel ce_count
	 */
	for (chan = 0; chan < csrow->nr_channels; chan++) {
		err = edac_create_channel_files(&csrow->kobj, chan);
		if (err) {
			/* special case the unregister here */
			kobject_put(&csrow->kobj);
			goto err_out;
		}
	}
	kobject_uevent(&csrow->kobj, KOBJ_ADD);
	return 0;

	/* error unwind stack */
err_release_top_kobj:
	kobject_put(&mci->edac_mci_kobj);

err_out:
	return err;
}