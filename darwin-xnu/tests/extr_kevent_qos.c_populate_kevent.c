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
struct kevent_qos_s {unsigned long long ident; int flags; int fflags; int data; int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_MACHPORT ; 
 int EV_ADD ; 
 int EV_DISPATCH ; 
 int EV_ENABLE ; 
 int EV_UDATA_SPECIFIC ; 
 int EV_VANISHED ; 
 int /*<<< orphan*/  MACH_MSG_TRAILER_FORMAT_0 ; 
 int MACH_RCV_LARGE ; 
 int MACH_RCV_LARGE_IDENTITY ; 
 int MACH_RCV_MSG ; 
 int /*<<< orphan*/  MACH_RCV_TRAILER_CTX ; 
 int MACH_RCV_TRAILER_ELEMENTS (int /*<<< orphan*/ ) ; 
 int MACH_RCV_TRAILER_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kevent_qos_s*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
populate_kevent(struct kevent_qos_s *kev, unsigned long long port)
{

	memset(kev, 0, sizeof(struct kevent_qos_s));
	kev->ident = port;
	kev->filter = EVFILT_MACHPORT;
	kev->flags = EV_ADD | EV_ENABLE | EV_UDATA_SPECIFIC | EV_DISPATCH | EV_VANISHED;
	kev->fflags = (MACH_RCV_MSG | MACH_RCV_LARGE | MACH_RCV_LARGE_IDENTITY |
		MACH_RCV_TRAILER_ELEMENTS(MACH_RCV_TRAILER_CTX) |
		MACH_RCV_TRAILER_TYPE(MACH_MSG_TRAILER_FORMAT_0));
	kev->data = 1;

}