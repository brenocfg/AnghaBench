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
typedef  int uint32_t ;
struct knote {int kn_sfflags; scalar_t__ kn_hookid; int /*<<< orphan*/  kn_sdata; } ;
struct kevent_internal_s {int fflags; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ FILTER_ACTIVE ; 
#define  NOTE_FFAND 131 
#define  NOTE_FFCOPY 130 
 int NOTE_FFCTRLMASK ; 
 int NOTE_FFLAGSMASK ; 
#define  NOTE_FFNOP 129 
#define  NOTE_FFOR 128 
 int NOTE_TRIGGER ; 

__attribute__((used)) static int
filt_usertouch(struct knote *kn, struct kevent_internal_s *kev)
{
	uint32_t ffctrl;
	int fflags;

	ffctrl = kev->fflags & NOTE_FFCTRLMASK;
	fflags = kev->fflags & NOTE_FFLAGSMASK;
	switch (ffctrl) {
	case NOTE_FFNOP:
		break;
	case NOTE_FFAND:
		kn->kn_sfflags &= fflags;
		break;
	case NOTE_FFOR:
		kn->kn_sfflags |= fflags;
		break;
	case NOTE_FFCOPY:
		kn->kn_sfflags = fflags;
		break;
	}
	kn->kn_sdata = kev->data;

	if (kev->fflags & NOTE_TRIGGER) {
		kn->kn_hookid = FILTER_ACTIVE;
	}
	return (int)kn->kn_hookid;
}