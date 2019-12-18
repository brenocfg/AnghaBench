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
struct bfad_fcxp {struct bfa_sge_s* req_sge; } ;
struct bfa_sge_s {scalar_t__ sg_addr; } ;

/* Variables and functions */

u64
bfad_fcxp_get_req_sgaddr_cb(void *bfad_fcxp, int sgeid)
{
	struct bfad_fcxp	*drv_fcxp = bfad_fcxp;
	struct bfa_sge_s  *sge;
	u64	addr;

	sge = drv_fcxp->req_sge + sgeid;
	addr = (u64)(size_t) sge->sg_addr;
	return addr;
}