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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
struct vfe_output_path {int fragIndex; scalar_t__ hwCurrentFlag; int /*<<< orphan*/  hwRegPongAddress; int /*<<< orphan*/  hwRegPingAddress; int /*<<< orphan*/ * addressBuffer; } ;

/* Variables and functions */
 scalar_t__ ping ; 
 scalar_t__ pong ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_process_pingpong_irq(struct vfe_output_path *in,
	uint8_t fragmentCount)
{
	uint16_t circularIndex;
	uint32_t nextFragmentAddr;

	/* get next fragment address from circular buffer */
	circularIndex    = (in->fragIndex) % (2 * fragmentCount);
	nextFragmentAddr = in->addressBuffer[circularIndex];

	in->fragIndex = circularIndex + 1;

	/* use next fragment to program hardware ping/pong address. */
	if (in->hwCurrentFlag == ping) {
		writel(nextFragmentAddr, in->hwRegPingAddress);
		in->hwCurrentFlag = pong;

	} else {
		writel(nextFragmentAddr, in->hwRegPongAddress);
		in->hwCurrentFlag = ping;
	}
}