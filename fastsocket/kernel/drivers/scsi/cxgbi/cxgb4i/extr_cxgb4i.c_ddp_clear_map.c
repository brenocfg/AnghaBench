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
struct cxgbi_hba {int /*<<< orphan*/  port_id; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 unsigned int ULPMEM_IDATA_MAX_NPPODS ; 
 int ddp_ppod_write_idata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ddp_clear_map(struct cxgbi_hba *chba, unsigned int tag,
			  unsigned int idx, unsigned int npods)
{
	unsigned int i, cnt;
	int err;

	for (i = 0; i < npods; i += cnt, idx += cnt) {
		cnt = npods - i;
		if (cnt > ULPMEM_IDATA_MAX_NPPODS)
			cnt = ULPMEM_IDATA_MAX_NPPODS;
		err = ddp_ppod_write_idata(chba->cdev, chba->port_id, NULL,
					idx, cnt, NULL, 0);
		if (err < 0)
			break;
	}
}