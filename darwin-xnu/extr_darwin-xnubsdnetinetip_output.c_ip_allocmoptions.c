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
struct ip_moptions {int /*<<< orphan*/  imo_trace; int /*<<< orphan*/  imo_debug; int /*<<< orphan*/  imo_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFD_ALLOC ; 
 int /*<<< orphan*/  IFD_DEBUG ; 
 int /*<<< orphan*/  IMO_ADDREF (struct ip_moptions*) ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct ip_moptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifa_mtx_attr ; 
 int /*<<< orphan*/  ifa_mtx_grp ; 
 scalar_t__ imo_debug ; 
 int /*<<< orphan*/  imo_size ; 
 int /*<<< orphan*/  imo_trace ; 
 int /*<<< orphan*/  imo_zone ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_moptions* zalloc (int /*<<< orphan*/ ) ; 
 struct ip_moptions* zalloc_noblock (int /*<<< orphan*/ ) ; 

struct ip_moptions *
ip_allocmoptions(int how)
{
	struct ip_moptions *imo;

	imo = (how == M_WAITOK) ? zalloc(imo_zone) : zalloc_noblock(imo_zone);
	if (imo != NULL) {
		bzero(imo, imo_size);
		lck_mtx_init(&imo->imo_lock, ifa_mtx_grp, ifa_mtx_attr);
		imo->imo_debug |= IFD_ALLOC;
		if (imo_debug != 0) {
			imo->imo_debug |= IFD_DEBUG;
			imo->imo_trace = imo_trace;
		}
		IMO_ADDREF(imo);
	}

	return (imo);
}