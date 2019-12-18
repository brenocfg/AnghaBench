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
struct mtd_info {struct efx_mtd* priv; } ;
struct erase_info {int fail_addr; int /*<<< orphan*/  state; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct efx_mtd {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* erase ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_ERASE_DONE ; 
 int /*<<< orphan*/  MTD_ERASE_FAILED ; 
 int /*<<< orphan*/  mtd_erase_callback (struct erase_info*) ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_mtd_erase(struct mtd_info *mtd, struct erase_info *erase)
{
	struct efx_mtd *efx_mtd = mtd->priv;
	int rc;

	rc = efx_mtd->ops->erase(mtd, erase->addr, erase->len);
	if (rc == 0) {
		erase->state = MTD_ERASE_DONE;
	} else {
		erase->state = MTD_ERASE_FAILED;
		erase->fail_addr = 0xffffffff;
	}
	mtd_erase_callback(erase);
	return rc;
}