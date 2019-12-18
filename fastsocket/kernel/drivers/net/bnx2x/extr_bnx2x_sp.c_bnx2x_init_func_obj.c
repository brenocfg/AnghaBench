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
struct bnx2x_func_sp_obj {struct bnx2x_func_sp_drv_ops* drv; int /*<<< orphan*/  wait_comp; int /*<<< orphan*/  complete_cmd; int /*<<< orphan*/  check_transition; int /*<<< orphan*/  send_cmd; void* afex_rdata_mapping; void* afex_rdata; void* rdata_mapping; void* rdata; int /*<<< orphan*/  one_pending_mutex; } ;
struct bnx2x_func_sp_drv_ops {int dummy; } ;
struct bnx2x {int dummy; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_func_chk_transition ; 
 int /*<<< orphan*/  bnx2x_func_comp_cmd ; 
 int /*<<< orphan*/  bnx2x_func_send_cmd ; 
 int /*<<< orphan*/  bnx2x_func_wait_comp ; 
 int /*<<< orphan*/  memset (struct bnx2x_func_sp_obj*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void bnx2x_init_func_obj(struct bnx2x *bp,
			 struct bnx2x_func_sp_obj *obj,
			 void *rdata, dma_addr_t rdata_mapping,
			 void *afex_rdata, dma_addr_t afex_rdata_mapping,
			 struct bnx2x_func_sp_drv_ops *drv_iface)
{
	memset(obj, 0, sizeof(*obj));

	mutex_init(&obj->one_pending_mutex);

	obj->rdata = rdata;
	obj->rdata_mapping = rdata_mapping;
	obj->afex_rdata = afex_rdata;
	obj->afex_rdata_mapping = afex_rdata_mapping;
	obj->send_cmd = bnx2x_func_send_cmd;
	obj->check_transition = bnx2x_func_chk_transition;
	obj->complete_cmd = bnx2x_func_comp_cmd;
	obj->wait_comp = bnx2x_func_wait_comp;

	obj->drv = drv_iface;
}