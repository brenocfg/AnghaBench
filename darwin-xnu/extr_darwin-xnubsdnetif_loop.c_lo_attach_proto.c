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
struct ifnet_attach_proto_param_v2 {int /*<<< orphan*/  pre_output; int /*<<< orphan*/  input; } ;
struct ifnet {int dummy; } ;
typedef  int protocol_family_t ;
typedef  int /*<<< orphan*/  proto ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  bzero (struct ifnet_attach_proto_param_v2*,int) ; 
 scalar_t__ ifnet_attach_protocol_v2 (struct ifnet*,int,struct ifnet_attach_proto_param_v2*) ; 
 int /*<<< orphan*/  lo_input ; 
 int /*<<< orphan*/  lo_pre_output ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__) ; 

__attribute__((used)) static errno_t
lo_attach_proto(struct ifnet *ifp, protocol_family_t protocol_family)
{
	struct ifnet_attach_proto_param_v2	proto;
	errno_t							result = 0;

	bzero(&proto, sizeof (proto));
	proto.input = lo_input;
	proto.pre_output = lo_pre_output;

	result = ifnet_attach_protocol_v2(ifp, protocol_family, &proto);

	if (result && result != EEXIST) {
		printf("lo_attach_proto: ifnet_attach_protocol for %u "
		    "returned=%d\n", protocol_family, result);
	}

	return (result);
}