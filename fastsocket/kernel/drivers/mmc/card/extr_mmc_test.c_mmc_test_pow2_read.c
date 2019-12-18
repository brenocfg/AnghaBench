#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct mmc_test_card {int /*<<< orphan*/  buffer; TYPE_2__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  read_partial; } ;
struct TYPE_4__ {TYPE_1__ csd; } ;

/* Variables and functions */
 int RESULT_UNSUP_CARD ; 
 int mmc_test_transfer (struct mmc_test_card*,struct scatterlist*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc_test_pow2_read(struct mmc_test_card *test)
{
	int ret, i;
	struct scatterlist sg;

	if (!test->card->csd.read_partial)
		return RESULT_UNSUP_CARD;

	for (i = 1; i < 512;i <<= 1) {
		sg_init_one(&sg, test->buffer, i);
		ret = mmc_test_transfer(test, &sg, 1, 0, 1, i, 0);
		if (ret)
			return ret;
	}

	return 0;
}