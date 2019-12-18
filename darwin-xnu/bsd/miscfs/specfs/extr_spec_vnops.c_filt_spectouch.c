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
struct knote {int /*<<< orphan*/  kn_sfflags; int /*<<< orphan*/  kn_sdata; } ;
struct kevent_internal_s {int flags; int /*<<< orphan*/  fflags; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EV_ENABLE ; 
 int spec_knote_select_and_link (struct knote*) ; 

__attribute__((used)) static int
filt_spectouch(struct knote *kn, struct kevent_internal_s *kev)
{
	kn->kn_sdata = kev->data;
	kn->kn_sfflags = kev->fflags;

	if (kev->flags & EV_ENABLE) {
		return spec_knote_select_and_link(kn);
	}

	return 0;
}