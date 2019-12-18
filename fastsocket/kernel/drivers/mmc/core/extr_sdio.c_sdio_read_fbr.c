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
struct sdio_func {unsigned char class; int /*<<< orphan*/  num; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 scalar_t__ SDIO_FBR_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ SDIO_FBR_STD_IF ; 
 scalar_t__ SDIO_FBR_STD_IF_EXT ; 
 int mmc_io_rw_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int sdio_read_fbr(struct sdio_func *func)
{
	int ret;
	unsigned char data;

	ret = mmc_io_rw_direct(func->card, 0, 0,
		SDIO_FBR_BASE(func->num) + SDIO_FBR_STD_IF, 0, &data);
	if (ret)
		goto out;

	data &= 0x0f;

	if (data == 0x0f) {
		ret = mmc_io_rw_direct(func->card, 0, 0,
			SDIO_FBR_BASE(func->num) + SDIO_FBR_STD_IF_EXT, 0, &data);
		if (ret)
			goto out;
	}

	func->class = data;

out:
	return ret;
}