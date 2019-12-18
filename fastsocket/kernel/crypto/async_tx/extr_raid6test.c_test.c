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
struct dma_async_tx_descriptor {int dummy; } ;
struct completion {int dummy; } ;
struct async_submit_ctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_TX_ACK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  addr_conv ; 
 struct dma_async_tx_descriptor* async_gen_syndrome (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct async_submit_ctl*) ; 
 int /*<<< orphan*/  async_tx_issue_pending (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  callback ; 
 void** data ; 
 int /*<<< orphan*/  dataptrs ; 
 int /*<<< orphan*/  init_async_submit (struct async_submit_ctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct completion*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  makedata (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  page_address (void*) ; 
 int /*<<< orphan*/  pr (char*,int) ; 
 void* recovi ; 
 void* recovj ; 
 void* spare ; 
 scalar_t__ test_disks (int,int,int) ; 
 scalar_t__ wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test(int disks, int *tests)
{
	struct dma_async_tx_descriptor *tx;
	struct async_submit_ctl submit;
	struct completion cmp;
	int err = 0;
	int i, j;

	recovi = data[disks];
	recovj = data[disks+1];
	spare  = data[disks+2];

	makedata(disks);

	/* Nuke syndromes */
	memset(page_address(data[disks-2]), 0xee, PAGE_SIZE);
	memset(page_address(data[disks-1]), 0xee, PAGE_SIZE);

	/* Generate assumed good syndrome */
	init_completion(&cmp);
	init_async_submit(&submit, ASYNC_TX_ACK, NULL, callback, &cmp, addr_conv);
	tx = async_gen_syndrome(dataptrs, 0, disks, PAGE_SIZE, &submit);
	async_tx_issue_pending(tx);

	if (wait_for_completion_timeout(&cmp, msecs_to_jiffies(3000)) == 0) {
		pr("error: initial gen_syndrome(%d) timed out\n", disks);
		return 1;
	}

	pr("testing the %d-disk case...\n", disks);
	for (i = 0; i < disks-1; i++)
		for (j = i+1; j < disks; j++) {
			(*tests)++;
			err += test_disks(i, j, disks);
		}

	return err;
}