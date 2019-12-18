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
struct cxgbi_sock {int /*<<< orphan*/  port_id; int /*<<< orphan*/  cdev; } ;
struct cxgbi_pagepod_hdr {int dummy; } ;
struct cxgbi_gather_list {int dummy; } ;

/* Variables and functions */
 unsigned int ULPMEM_IDATA_MAX_NPPODS ; 
 int ddp_ppod_write_idata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cxgbi_pagepod_hdr*,unsigned int,unsigned int,struct cxgbi_gather_list*,int) ; 

__attribute__((used)) static int ddp_set_map(struct cxgbi_sock *csk, struct cxgbi_pagepod_hdr *hdr,
			unsigned int idx, unsigned int npods,
			struct cxgbi_gather_list *gl)
{
	unsigned int i, cnt;
	int err = 0;

	for (i = 0; i < npods; i += cnt, idx += cnt) {
		cnt = npods - i;
		if (cnt > ULPMEM_IDATA_MAX_NPPODS)
			cnt = ULPMEM_IDATA_MAX_NPPODS;
		err = ddp_ppod_write_idata(csk->cdev, csk->port_id, hdr,
					idx, cnt, gl, 4 * i);
		if (err < 0)
			break;
	}
	return err;
}