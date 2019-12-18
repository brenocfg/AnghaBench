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
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum sum_check_flags { ____Placeholder_sum_check_flags } sum_check_flags ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct dma_async_tx_descriptor* __ioat3_prep_xor_lock (struct dma_chan*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,size_t,unsigned long) ; 

struct dma_async_tx_descriptor *
ioat3_prep_xor_val(struct dma_chan *chan, dma_addr_t *src,
		    unsigned int src_cnt, size_t len,
		    enum sum_check_flags *result, unsigned long flags)
{
	/* the cleanup routine only sets bits on validate failure, it
	 * does not clear bits on validate success... so clear it here
	 */
	*result = 0;

	return __ioat3_prep_xor_lock(chan, result, src[0], &src[1],
				     src_cnt - 1, len, flags);
}