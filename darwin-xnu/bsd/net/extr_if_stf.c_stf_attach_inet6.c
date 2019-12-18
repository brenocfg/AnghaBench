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
struct ifnet_attach_proto_param {int /*<<< orphan*/  pre_output; int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  scalar_t__ protocol_family_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ EPROTONOSUPPORT ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  bzero (struct ifnet_attach_proto_param*,int) ; 
 scalar_t__ ifnet_attach_protocol (int /*<<< orphan*/ ,scalar_t__,struct ifnet_attach_proto_param*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  stf_media_input ; 
 int /*<<< orphan*/  stf_pre_output ; 

__attribute__((used)) static errno_t
stf_attach_inet6(
	ifnet_t				ifp,
	protocol_family_t	protocol_family)
{
    struct ifnet_attach_proto_param	reg;
    errno_t							stat;
    
    if (protocol_family != PF_INET6)
    	return EPROTONOSUPPORT;

	bzero(&reg, sizeof(reg));
    reg.input = stf_media_input;
    reg.pre_output = stf_pre_output;

    stat = ifnet_attach_protocol(ifp, protocol_family, &reg);
    if (stat && stat != EEXIST) {
        printf("stf_attach_proto_family can't attach interface fam=%d\n",
        	   protocol_family);
    }

    return stat;
}