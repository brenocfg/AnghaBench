#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_4__ {scalar_t__* s6_addr16; } ;
struct sockaddr_in6 {int sin6_scope_id; TYPE_1__ sin6_addr; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ IN6_IS_ADDR_MC_INTFACELOCAL (TYPE_1__*) ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int if_index ; 
 int /*<<< orphan*/ ** ifindex2ifnet ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 int /*<<< orphan*/  ip6_sprintf (TYPE_1__*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int ntohs (scalar_t__) ; 

int
sa6_recoverscope(struct sockaddr_in6 *sin6, boolean_t attachcheck)
{
	u_int32_t zoneid;

	if (sin6->sin6_scope_id != 0) {
		log(LOG_NOTICE,
		    "sa6_recoverscope: assumption failure (non 0 ID): %s%%%d\n",
		    ip6_sprintf(&sin6->sin6_addr), sin6->sin6_scope_id);
		/* XXX: proceed anyway... */
	}
	if (IN6_IS_SCOPE_LINKLOCAL(&sin6->sin6_addr) ||
	    IN6_IS_ADDR_MC_INTFACELOCAL(&sin6->sin6_addr)) {
		/*
		 * KAME assumption: link id == interface id
		 */
		zoneid = ntohs(sin6->sin6_addr.s6_addr16[1]);
		if (zoneid) {
			/* sanity check */
			if (if_index < zoneid)
				return (ENXIO);
			/*
			 * We use the attachcheck parameter to skip the
			 * interface attachment check.
			 * Some callers might hold the ifnet_head lock in
			 * exclusive mode. This means that:
			 * 1) the interface can't go away -- hence we don't
			 *    need to perform this check
			 * 2) we can't perform this check because the lock is
			 *    in exclusive mode and trying to lock it in shared
			 *    mode would cause a deadlock.
			 */
			if (attachcheck) {
				ifnet_head_lock_shared();
				if (ifindex2ifnet[zoneid] == NULL) {
					ifnet_head_done();
					return (ENXIO);
				}
				ifnet_head_done();
			}
			sin6->sin6_addr.s6_addr16[1] = 0;
			sin6->sin6_scope_id = zoneid;
		}
	}

	return (0);
}