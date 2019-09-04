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
struct rtentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int rtrequest_locked (int,struct sockaddr*,struct sockaddr*,struct sockaddr*,int,struct rtentry**) ; 

int
rtrequest(int req, struct sockaddr *dst, struct sockaddr *gateway,
    struct sockaddr *netmask, int flags, struct rtentry **ret_nrt)
{
	int error;
	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_NOTOWNED);
	lck_mtx_lock(rnh_lock);
	error = rtrequest_locked(req, dst, gateway, netmask, flags, ret_nrt);
	lck_mtx_unlock(rnh_lock);
	return (error);
}