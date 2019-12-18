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
typedef  int /*<<< orphan*/  uint32_t ;
struct ledger_entry {int le_flags; } ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int LF_CALLED_BACK ; 
 int LF_WAKE_NEEDED ; 
 int /*<<< orphan*/  flag_clear (int*,int) ; 
 int /*<<< orphan*/  limit_exceeded (struct ledger_entry*) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ledger_limit_entry_wakeup(struct ledger_entry *le)
{
	uint32_t flags;

	if (!limit_exceeded(le)) {
		flags = flag_clear(&le->le_flags, LF_CALLED_BACK);

		while (le->le_flags & LF_WAKE_NEEDED) {
			flag_clear(&le->le_flags, LF_WAKE_NEEDED);
			thread_wakeup((event_t)le);
		}
	}
}