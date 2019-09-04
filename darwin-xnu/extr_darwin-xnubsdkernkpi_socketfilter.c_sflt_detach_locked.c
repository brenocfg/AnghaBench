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
struct socket_filter_entry {int sfe_flags; } ;

/* Variables and functions */
 int SFEF_ATTACHED ; 
 int /*<<< orphan*/  sflt_entry_release (struct socket_filter_entry*) ; 

__attribute__((used)) static void
sflt_detach_locked(struct socket_filter_entry *entry)
{
	if ((entry->sfe_flags & SFEF_ATTACHED) != 0) {
		entry->sfe_flags &= ~SFEF_ATTACHED;
		sflt_entry_release(entry);
	}
}