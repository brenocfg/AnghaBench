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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct ccid_operations {scalar_t__ (* ccid_hc_rx_init ) (struct ccid*,struct sock*) ;scalar_t__ (* ccid_hc_tx_init ) (struct ccid*,struct sock*) ;int /*<<< orphan*/  ccid_hc_tx_slab; int /*<<< orphan*/  ccid_hc_rx_slab; int /*<<< orphan*/  ccid_hc_tx_obj_size; int /*<<< orphan*/  ccid_hc_rx_obj_size; } ;
struct ccid {struct ccid_operations* ccid_ops; } ;

/* Variables and functions */
 struct ccid_operations* ccid_by_number (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gfp_any () ; 
 struct ccid* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ccid*) ; 
 int /*<<< orphan*/  memset (struct ccid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ccid*,struct sock*) ; 
 scalar_t__ stub2 (struct ccid*,struct sock*) ; 

struct ccid *ccid_new(const u8 id, struct sock *sk, bool rx)
{
	struct ccid_operations *ccid_ops = ccid_by_number(id);
	struct ccid *ccid = NULL;

	if (ccid_ops == NULL)
		goto out;

	ccid = kmem_cache_alloc(rx ? ccid_ops->ccid_hc_rx_slab :
				     ccid_ops->ccid_hc_tx_slab, gfp_any());
	if (ccid == NULL)
		goto out;
	ccid->ccid_ops = ccid_ops;
	if (rx) {
		memset(ccid + 1, 0, ccid_ops->ccid_hc_rx_obj_size);
		if (ccid->ccid_ops->ccid_hc_rx_init != NULL &&
		    ccid->ccid_ops->ccid_hc_rx_init(ccid, sk) != 0)
			goto out_free_ccid;
	} else {
		memset(ccid + 1, 0, ccid_ops->ccid_hc_tx_obj_size);
		if (ccid->ccid_ops->ccid_hc_tx_init != NULL &&
		    ccid->ccid_ops->ccid_hc_tx_init(ccid, sk) != 0)
			goto out_free_ccid;
	}
out:
	return ccid;
out_free_ccid:
	kmem_cache_free(rx ? ccid_ops->ccid_hc_rx_slab :
			ccid_ops->ccid_hc_tx_slab, ccid);
	ccid = NULL;
	goto out;
}