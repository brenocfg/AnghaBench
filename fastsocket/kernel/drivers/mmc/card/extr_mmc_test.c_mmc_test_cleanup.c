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
struct mmc_test_card {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mmc_test_buffer_transfer (struct mmc_test_card*,int /*<<< orphan*/ ,int,int,int) ; 
 int mmc_test_set_blksize (struct mmc_test_card*,int) ; 

__attribute__((used)) static int mmc_test_cleanup(struct mmc_test_card *test)
{
	int ret, i;

	ret = mmc_test_set_blksize(test, 512);
	if (ret)
		return ret;

	memset(test->buffer, 0, 512);

	for (i = 0;i < BUFFER_SIZE / 512;i++) {
		ret = mmc_test_buffer_transfer(test, test->buffer, i * 512, 512, 1);
		if (ret)
			return ret;
	}

	return 0;
}