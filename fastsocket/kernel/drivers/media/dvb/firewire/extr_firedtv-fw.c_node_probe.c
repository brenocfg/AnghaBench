#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct firedtv {int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  directory; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_MODEL ; 
 int ENOMEM ; 
 int MAX_MODEL_NAME_LEN ; 
 int avc_identify_subunit (struct firedtv*) ; 
 int /*<<< orphan*/  avc_register_remote_control (struct firedtv*) ; 
 int /*<<< orphan*/  backend ; 
 struct firedtv* fdtv_alloc (struct device*,int /*<<< orphan*/ *,char*,int) ; 
 int fdtv_dvb_register (struct firedtv*) ; 
 int fdtv_register_rc (struct firedtv*,struct device*) ; 
 int /*<<< orphan*/  fdtv_unregister_rc (struct firedtv*) ; 
 int fw_csr_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* fw_unit (struct device*) ; 
 int /*<<< orphan*/  kfree (struct firedtv*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_list ; 
 int /*<<< orphan*/  node_list_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int node_probe(struct device *dev)
{
	struct firedtv *fdtv;
	char name[MAX_MODEL_NAME_LEN];
	int name_len, err;

	name_len = fw_csr_string(fw_unit(dev)->directory, CSR_MODEL,
				 name, sizeof(name));

	fdtv = fdtv_alloc(dev, &backend, name, name_len >= 0 ? name_len : 0);
	if (!fdtv)
		return -ENOMEM;

	err = fdtv_register_rc(fdtv, dev);
	if (err)
		goto fail_free;

	spin_lock_irq(&node_list_lock);
	list_add_tail(&fdtv->list, &node_list);
	spin_unlock_irq(&node_list_lock);

	err = avc_identify_subunit(fdtv);
	if (err)
		goto fail;

	err = fdtv_dvb_register(fdtv);
	if (err)
		goto fail;

	avc_register_remote_control(fdtv);

	return 0;
fail:
	spin_lock_irq(&node_list_lock);
	list_del(&fdtv->list);
	spin_unlock_irq(&node_list_lock);
	fdtv_unregister_rc(fdtv);
fail_free:
	kfree(fdtv);

	return err;
}