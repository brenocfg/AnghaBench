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
struct ohci_hcd {int dummy; } ;
struct ed {int /*<<< orphan*/  td_list; int /*<<< orphan*/  hwTailP; int /*<<< orphan*/  hwHeadP; int /*<<< orphan*/  hwINFO; } ;

/* Variables and functions */
 int ED_IN ; 
 int TD_MASK ; 
 int hc32_to_cpu (struct ohci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_ed(struct ohci_hcd *ohci, struct ed *ed)
{
	return (hc32_to_cpu(ohci, ed->hwINFO) & ED_IN) != 0
		&& (hc32_to_cpu(ohci, ed->hwHeadP) & TD_MASK)
			== (hc32_to_cpu(ohci, ed->hwTailP) & TD_MASK)
		&& !list_empty(&ed->td_list);
}