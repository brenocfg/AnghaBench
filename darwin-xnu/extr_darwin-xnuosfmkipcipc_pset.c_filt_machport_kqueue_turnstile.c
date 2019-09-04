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
struct turnstile {int dummy; } ;
struct knote {int kn_sfflags; int kn_status; } ;

/* Variables and functions */
 int KN_DISPATCH ; 
 int MACH_RCV_MSG ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  knote_get_kq (struct knote*) ; 
 struct turnstile* kqueue_turnstile (int /*<<< orphan*/ ) ; 

struct turnstile *
filt_machport_kqueue_turnstile(struct knote *kn)
{
	if ((kn->kn_sfflags & MACH_RCV_MSG) && (kn->kn_status & KN_DISPATCH)) {
		return kqueue_turnstile(knote_get_kq(kn));
	}
	return TURNSTILE_NULL;
}