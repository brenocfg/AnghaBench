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
struct ifnet_attach_proto_param {int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int protocol_family_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  bzero (struct ifnet_attach_proto_param*,int) ; 
 int /*<<< orphan*/  gif_input ; 
 scalar_t__ ifnet_attach_protocol (int /*<<< orphan*/ ,int,struct ifnet_attach_proto_param*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static errno_t
gif_attach_proto_family(
	ifnet_t ifp,
	protocol_family_t protocol_family)
{
	struct ifnet_attach_proto_param reg;
	errno_t stat;

	bzero(&reg, sizeof (reg));
	reg.input = gif_input;

	stat = ifnet_attach_protocol(ifp, protocol_family, &reg);
	if (stat && stat != EEXIST) {
		printf("gif_attach_proto_family can't attach interface	\
		    fam=%d\n", protocol_family);
	}

	return (stat);
}