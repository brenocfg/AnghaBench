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
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int RTF_IFSCOPE ; 
 int rtrequest_common_locked (int,struct sockaddr*,struct sockaddr*,struct sockaddr*,int,struct rtentry**,int /*<<< orphan*/ ) ; 

int
rtrequest_locked(int req, struct sockaddr *dst, struct sockaddr *gateway,
    struct sockaddr *netmask, int flags, struct rtentry **ret_nrt)
{
	return (rtrequest_common_locked(req, dst, gateway, netmask,
	    (flags & ~RTF_IFSCOPE), ret_nrt, IFSCOPE_NONE));
}