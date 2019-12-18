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
struct scatterlist {int dummy; } ;
struct mmc_test_card {scalar_t__ buffer; } ;

/* Variables and functions */
 int mmc_test_transfer (struct mmc_test_card*,struct scatterlist*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,scalar_t__,int) ; 

__attribute__((used)) static int mmc_test_align_read(struct mmc_test_card *test)
{
	int ret, i;
	struct scatterlist sg;

	for (i = 1;i < 4;i++) {
		sg_init_one(&sg, test->buffer + i, 512);
		ret = mmc_test_transfer(test, &sg, 1, 0, 1, 512, 0);
		if (ret)
			return ret;
	}

	return 0;
}