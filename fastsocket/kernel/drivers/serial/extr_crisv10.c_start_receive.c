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
struct e100_serial {int /*<<< orphan*/ * icmdadr; scalar_t__ uses_dma_in; } ;

/* Variables and functions */
 scalar_t__ IO_EXTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IO_STATE_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_DMA_CH6_CMD ; 
 int /*<<< orphan*/  cmd ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  start_recv_dma (struct e100_serial*) ; 

__attribute__((used)) static void
start_receive(struct e100_serial *info)
{
#ifdef CONFIG_SVINTO_SIM
	/* No receive in the simulator.  Will probably be when the rest of
	 * the serial interface works, and this piece will just be removed.
	 */
	return;
#endif
	if (info->uses_dma_in) {
		/* reset the input dma channel to be sure it works */

		*info->icmdadr = IO_STATE(R_DMA_CH6_CMD, cmd, reset);
		while (IO_EXTRACT(R_DMA_CH6_CMD, cmd, *info->icmdadr) ==
		       IO_STATE_VALUE(R_DMA_CH6_CMD, cmd, reset));

		start_recv_dma(info);
	}
}