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
struct ccid_operations {int /*<<< orphan*/ * ccid_hc_rx_slab; int /*<<< orphan*/  ccid_name; int /*<<< orphan*/  ccid_id; int /*<<< orphan*/ * ccid_hc_tx_slab; int /*<<< orphan*/  ccid_hc_tx_slab_name; int /*<<< orphan*/  ccid_hc_tx_obj_size; int /*<<< orphan*/  ccid_hc_rx_slab_name; int /*<<< orphan*/  ccid_hc_rx_obj_size; } ;

/* Variables and functions */
 int ENOBUFS ; 
 void* ccid_kmem_cache_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccid_kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccid_activate(struct ccid_operations *ccid_ops)
{
	int err = -ENOBUFS;

	ccid_ops->ccid_hc_rx_slab =
			ccid_kmem_cache_create(ccid_ops->ccid_hc_rx_obj_size,
					       ccid_ops->ccid_hc_rx_slab_name,
					       "ccid%u_hc_rx_sock",
					       ccid_ops->ccid_id);
	if (ccid_ops->ccid_hc_rx_slab == NULL)
		goto out;

	ccid_ops->ccid_hc_tx_slab =
			ccid_kmem_cache_create(ccid_ops->ccid_hc_tx_obj_size,
					       ccid_ops->ccid_hc_tx_slab_name,
					       "ccid%u_hc_tx_sock",
					       ccid_ops->ccid_id);
	if (ccid_ops->ccid_hc_tx_slab == NULL)
		goto out_free_rx_slab;

	pr_info("CCID: Activated CCID %d (%s)\n",
		ccid_ops->ccid_id, ccid_ops->ccid_name);
	err = 0;
out:
	return err;
out_free_rx_slab:
	ccid_kmem_cache_destroy(ccid_ops->ccid_hc_rx_slab);
	ccid_ops->ccid_hc_rx_slab = NULL;
	goto out;
}