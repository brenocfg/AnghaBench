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
typedef  int u8 ;
struct ehci_qh {unsigned int gap_uf; scalar_t__ c_usecs; int /*<<< orphan*/  period; int /*<<< orphan*/  dev; int /*<<< orphan*/  tt_usecs; scalar_t__ usecs; } ;
struct ehci_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  __hc32 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  check_period (struct ehci_hcd*,unsigned int,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_hc32 (struct ehci_hcd*,int) ; 
 scalar_t__ tt_available (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ tt_no_collision (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int check_intr_schedule (
	struct ehci_hcd		*ehci,
	unsigned		frame,
	unsigned		uframe,
	const struct ehci_qh	*qh,
	__hc32			*c_maskp
)
{
	int		retval = -ENOSPC;
	u8		mask = 0;

	if (qh->c_usecs && uframe >= 6)		/* FSTN territory? */
		goto done;

	if (!check_period (ehci, frame, uframe, qh->period, qh->usecs))
		goto done;
	if (!qh->c_usecs) {
		retval = 0;
		*c_maskp = 0;
		goto done;
	}

#ifdef CONFIG_USB_EHCI_TT_NEWSCHED
	if (tt_available (ehci, qh->period, qh->dev, frame, uframe,
				qh->tt_usecs)) {
		unsigned i;

		/* TODO : this may need FSTN for SSPLIT in uframe 5. */
		for (i=uframe+1; i<8 && i<uframe+4; i++)
			if (!check_period (ehci, frame, i,
						qh->period, qh->c_usecs))
				goto done;
			else
				mask |= 1 << i;

		retval = 0;

		*c_maskp = cpu_to_hc32(ehci, mask << 8);
	}
#else
	/* Make sure this tt's buffer is also available for CSPLITs.
	 * We pessimize a bit; probably the typical full speed case
	 * doesn't need the second CSPLIT.
	 *
	 * NOTE:  both SPLIT and CSPLIT could be checked in just
	 * one smart pass...
	 */
	mask = 0x03 << (uframe + qh->gap_uf);
	*c_maskp = cpu_to_hc32(ehci, mask << 8);

	mask |= 1 << uframe;
	if (tt_no_collision (ehci, qh->period, qh->dev, frame, mask)) {
		if (!check_period (ehci, frame, uframe + qh->gap_uf + 1,
					qh->period, qh->c_usecs))
			goto done;
		if (!check_period (ehci, frame, uframe + qh->gap_uf,
					qh->period, qh->c_usecs))
			goto done;
		retval = 0;
	}
#endif
done:
	return retval;
}