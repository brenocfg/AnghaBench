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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_VLAN ; 
 int ifnet_detach_protocol (struct ifnet*,int /*<<< orphan*/ ) ; 
 char* ifnet_name (struct ifnet*) ; 
 int ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

__attribute__((used)) static int
vlan_detach_protocol(struct ifnet *ifp)
{
    int         error;

    error = ifnet_detach_protocol(ifp, PF_VLAN);
    if (error) {
	printf("vlan_proto_detach(%s%d) ifnet_detach_protocol failed, %d\n",
	       ifnet_name(ifp), ifnet_unit(ifp), error);
    }
	
    return (error);
}