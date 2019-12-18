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
typedef  int uint32_t ;
struct socket {int so_flags; TYPE_1__* so_cfil; } ;
struct cfil_entry {int cfe_flags; int /*<<< orphan*/ * cfe_filter; } ;
struct TYPE_2__ {struct cfil_entry* cfi_entries; } ;

/* Variables and functions */
 int CFEF_CFIL_DETACHED ; 
 int CFEF_SENT_SOCK_ATTACHED ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IS_UDP (struct socket*) ; 
 int MAX_CONTENT_FILTER ; 
 int SOF_CONTENT_FILTER ; 
 int cfil_filters_udp_attached (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

__attribute__((used)) static int
cfil_filters_attached(struct socket *so)
{
	struct cfil_entry *entry;
	uint32_t kcunit;
	int attached = 0;

	if (IS_UDP(so)) {
		return cfil_filters_udp_attached(so, FALSE);
	}

	if ((so->so_flags & SOF_CONTENT_FILTER) == 0 || so->so_cfil == NULL)
		return (0);

	socket_lock_assert_owned(so);

	for (kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
		entry = &so->so_cfil->cfi_entries[kcunit - 1];

		/* Are we attached to the filter? */
		if (entry->cfe_filter == NULL)
			continue;
		if ((entry->cfe_flags & CFEF_SENT_SOCK_ATTACHED) == 0)
			continue;
		if ((entry->cfe_flags & CFEF_CFIL_DETACHED) != 0)
			continue;
		attached = 1;
		break;
	}

	return (attached);
}