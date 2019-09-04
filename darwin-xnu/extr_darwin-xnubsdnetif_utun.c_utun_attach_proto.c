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
typedef  int protocol_family_t ;
typedef  int /*<<< orphan*/  proto ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  bzero (struct ifnet_attach_proto_param*,int) ; 
 scalar_t__ ifnet_attach_protocol (int /*<<< orphan*/ ,int,struct ifnet_attach_proto_param*) ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  utun_proto_input ; 
 int /*<<< orphan*/  utun_proto_pre_output ; 

__attribute__((used)) static errno_t
utun_attach_proto(ifnet_t interface,
				  protocol_family_t protocol)
{
	struct ifnet_attach_proto_param	proto;
	
	bzero(&proto, sizeof(proto));
	proto.input = utun_proto_input;
	proto.pre_output = utun_proto_pre_output;

	errno_t result = ifnet_attach_protocol(interface, protocol, &proto);
	if (result != 0 && result != EEXIST) {
		printf("utun_attach_inet - ifnet_attach_protocol %d failed: %d\n",
			protocol, result);
	}
	
	return result;
}