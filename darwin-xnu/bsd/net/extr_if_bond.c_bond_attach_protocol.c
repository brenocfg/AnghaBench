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
 int /*<<< orphan*/  PF_BOND ; 
 int /*<<< orphan*/  bond_detached ; 
 int /*<<< orphan*/  bond_event ; 
 int /*<<< orphan*/  bond_input ; 
 int /*<<< orphan*/  bzero (struct ifnet_attach_proto_param*,int) ; 
 int ifnet_attach_protocol (struct ifnet*,int /*<<< orphan*/ ,struct ifnet_attach_proto_param*) ; 
 char* ifnet_name (struct ifnet*) ; 
 int ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

__attribute__((used)) static int
bond_attach_protocol(struct ifnet *ifp)
{
    int								error;
    struct ifnet_attach_proto_param	reg;
	
    bzero(&reg, sizeof(reg));
    reg.input = bond_input;
    reg.event = bond_event;
    reg.detached = bond_detached;
	
    error = ifnet_attach_protocol(ifp, PF_BOND, &reg);
    if (error) {
	printf("bond over %s%d: ifnet_attach_protocol failed, %d\n",
	       ifnet_name(ifp), ifnet_unit(ifp), error);
    }
    return (error);
}