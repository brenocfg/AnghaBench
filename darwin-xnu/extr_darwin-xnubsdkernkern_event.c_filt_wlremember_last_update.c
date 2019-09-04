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
struct knote {int kn_data; int /*<<< orphan*/  kn_ext; int /*<<< orphan*/  kn_fflags; } ;
struct kevent_internal_s {int /*<<< orphan*/  ext; int /*<<< orphan*/  fflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
filt_wlremember_last_update(struct knote *kn, struct kevent_internal_s *kev,
		int error)
{
	kn->kn_fflags = kev->fflags;
	kn->kn_data = error;
	memcpy(kn->kn_ext, kev->ext, sizeof(kev->ext));
}