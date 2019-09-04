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
struct ifnet_attach_proto_param {int /*<<< orphan*/  detached; int /*<<< orphan*/  event; int /*<<< orphan*/  input; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  PF_VLAN ; 
 int /*<<< orphan*/  bzero (struct ifnet_attach_proto_param*,int) ; 
 int ifnet_attach_protocol (struct ifnet*,int /*<<< orphan*/ ,struct ifnet_attach_proto_param*) ; 
 char* ifnet_name (struct ifnet*) ; 
 int ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int /*<<< orphan*/  vlan_detached ; 
 int /*<<< orphan*/  vlan_event ; 
 int /*<<< orphan*/  vlan_input ; 

__attribute__((used)) static int
vlan_attach_protocol(struct ifnet *ifp)
{
    int								error;
    struct ifnet_attach_proto_param	reg;
	
    bzero(&reg, sizeof(reg));
    reg.input            = vlan_input;
    reg.event            = vlan_event;
    reg.detached         = vlan_detached;
    error = ifnet_attach_protocol(ifp, PF_VLAN, &reg);
    if (error) {
	printf("vlan_proto_attach(%s%d) ifnet_attach_protocol failed, %d\n",
	       ifnet_name(ifp), ifnet_unit(ifp), error);
    }
    return (error);
}