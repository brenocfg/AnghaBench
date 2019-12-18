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
struct ehci_iso_sched {int /*<<< orphan*/  td_list; } ;
struct ehci_iso_packet {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ehci_iso_sched* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ehci_iso_sched *
iso_sched_alloc (unsigned packets, gfp_t mem_flags)
{
	struct ehci_iso_sched	*iso_sched;
	int			size = sizeof *iso_sched;

	size += packets * sizeof (struct ehci_iso_packet);
	iso_sched = kzalloc(size, mem_flags);
	if (likely (iso_sched != NULL)) {
		INIT_LIST_HEAD (&iso_sched->td_list);
	}
	return iso_sched;
}