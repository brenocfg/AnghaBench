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
struct sockaddr {int dummy; } ;
struct ifaddr {int dummy; } ;

/* Variables and functions */
 struct ifaddr* ifa_ifwithroute_locked (int,struct sockaddr const*,struct sockaddr const*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 

struct ifaddr *
ifa_ifwithroute(
	int flags,
	const struct sockaddr	*dst,
	const struct sockaddr *gateway)
{
	struct ifaddr *ifa;

	lck_mtx_lock(rnh_lock);
	ifa = ifa_ifwithroute_locked(flags, dst, gateway);
	lck_mtx_unlock(rnh_lock);

	return (ifa);
}