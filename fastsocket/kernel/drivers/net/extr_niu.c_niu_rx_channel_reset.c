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
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXDMA_CFIG1 (int) ; 
 int /*<<< orphan*/  RXDMA_CFIG1_RST ; 
 int niu_set_and_wait_clear (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 

__attribute__((used)) static int niu_rx_channel_reset(struct niu *np, int channel)
{
	return niu_set_and_wait_clear(np, RXDMA_CFIG1(channel),
				      RXDMA_CFIG1_RST, 1000, 10,
				      "RXDMA_CFIG1");
}