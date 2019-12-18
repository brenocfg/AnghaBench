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
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int max_blk_count; int max_req_size; int max_seg_size; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int RESULT_UNSUP_HOST ; 
 unsigned int min (unsigned int,int) ; 
 int mmc_test_transfer (struct mmc_test_card*,struct scatterlist*,int,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mmc_test_multi_write(struct mmc_test_card *test)
{
	int ret;
	unsigned int size;
	struct scatterlist sg;

	if (test->card->host->max_blk_count == 1)
		return RESULT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->card->host->max_req_size);
	size = min(size, test->card->host->max_seg_size);
	size = min(size, test->card->host->max_blk_count * 512);

	if (size < 1024)
		return RESULT_UNSUP_HOST;

	sg_init_one(&sg, test->buffer, size);

	ret = mmc_test_transfer(test, &sg, 1, 0, size/512, 512, 1);
	if (ret)
		return ret;

	return 0;
}