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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct sockaddr const*,int,int) ; 
 int /*<<< orphan*/  proc_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skywalk_flow_check_connect ; 

int
mac_skywalk_flow_check_connect(proc_t proc, void *flow, const struct sockaddr *addr, int type, int protocol)
{
	int error;

	MAC_CHECK(skywalk_flow_check_connect, proc_ucred(proc), flow, addr, type, protocol);
	return (error);
}