#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct llinfo_arp {int /*<<< orphan*/  la_holdq; scalar_t__ la_prbreq_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  held; int /*<<< orphan*/  purged; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _flushq (int /*<<< orphan*/ *) ; 
 TYPE_1__ arpstat ; 
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qempty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
arp_llinfo_flushq(struct llinfo_arp *la)
{
	uint32_t held = qlen(&la->la_holdq);

	if (held != 0) {
		atomic_add_32(&arpstat.purged, held);
		atomic_add_32(&arpstat.held, -held);
		_flushq(&la->la_holdq);
	}
	la->la_prbreq_cnt = 0;
	VERIFY(qempty(&la->la_holdq));
	return (held);
}