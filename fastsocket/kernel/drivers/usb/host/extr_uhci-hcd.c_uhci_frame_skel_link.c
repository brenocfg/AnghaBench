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
struct uhci_hcd {int /*<<< orphan*/ * skelqh; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_TO_QH (int /*<<< orphan*/ ) ; 
 int UHCI_NUMFRAMES ; 
 scalar_t__ __ffs (int) ; 

__attribute__((used)) static __le32 uhci_frame_skel_link(struct uhci_hcd *uhci, int frame)
{
	int skelnum;

	/*
	 * The interrupt queues will be interleaved as evenly as possible.
	 * There's not much to be done about period-1 interrupts; they have
	 * to occur in every frame.  But we can schedule period-2 interrupts
	 * in odd-numbered frames, period-4 interrupts in frames congruent
	 * to 2 (mod 4), and so on.  This way each frame only has two
	 * interrupt QHs, which will help spread out bandwidth utilization.
	 *
	 * ffs (Find First bit Set) does exactly what we need:
	 * 1,3,5,...  => ffs = 0 => use period-2 QH = skelqh[8],
	 * 2,6,10,... => ffs = 1 => use period-4 QH = skelqh[7], etc.
	 * ffs >= 7 => not on any high-period queue, so use
	 *	period-1 QH = skelqh[9].
	 * Add in UHCI_NUMFRAMES to insure at least one bit is set.
	 */
	skelnum = 8 - (int) __ffs(frame | UHCI_NUMFRAMES);
	if (skelnum <= 1)
		skelnum = 9;
	return LINK_TO_QH(uhci->skelqh[skelnum]);
}