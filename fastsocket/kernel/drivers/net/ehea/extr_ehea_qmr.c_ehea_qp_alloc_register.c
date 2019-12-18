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
typedef  scalar_t__ u64 ;
struct hw_queue {int dummy; } ;
struct ehea_qp {int /*<<< orphan*/  fw_handle; } ;
struct ehea_adapter {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_PAGESIZE ; 
 int EIO ; 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  ehea_error (char*) ; 
 scalar_t__ ehea_h_register_rpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  hw_qeit_reset (struct hw_queue*) ; 
 void* hw_qpageit_get_inc (struct hw_queue*) ; 
 int hw_queue_ctor (struct hw_queue*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_queue_dtor (struct hw_queue*) ; 
 scalar_t__ virt_to_abs (void*) ; 

__attribute__((used)) static int ehea_qp_alloc_register(struct ehea_qp *qp, struct hw_queue *hw_queue,
			   int nr_pages, int wqe_size, int act_nr_sges,
			   struct ehea_adapter *adapter, int h_call_q_selector)
{
	u64 hret, rpage;
	int ret, cnt;
	void *vpage;

	ret = hw_queue_ctor(hw_queue, nr_pages, EHEA_PAGESIZE, wqe_size);
	if (ret)
		return ret;

	for (cnt = 0; cnt < nr_pages; cnt++) {
		vpage = hw_qpageit_get_inc(hw_queue);
		if (!vpage) {
			ehea_error("hw_qpageit_get_inc failed");
			goto out_kill_hwq;
		}
		rpage = virt_to_abs(vpage);
		hret = ehea_h_register_rpage(adapter->handle,
					     0, h_call_q_selector,
					     qp->fw_handle, rpage, 1);
		if (hret < H_SUCCESS) {
			ehea_error("register_rpage_qp failed");
			goto out_kill_hwq;
		}
	}
	hw_qeit_reset(hw_queue);
	return 0;

out_kill_hwq:
	hw_queue_dtor(hw_queue);
	return -EIO;
}