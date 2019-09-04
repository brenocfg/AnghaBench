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
struct ndrv_cb {scalar_t__ nd_proto_family; int /*<<< orphan*/  nd_if; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PF_NDRV ; 
 int ifnet_detach_protocol (int /*<<< orphan*/ ,scalar_t__) ; 

int
ndrv_delspec(struct ndrv_cb *np)
{
    int result = 0;

    if (np->nd_proto_family == PF_NDRV ||
    	np->nd_proto_family == 0)
        return EINVAL;

    /* Detach the protocol */
    result = ifnet_detach_protocol(np->nd_if, np->nd_proto_family);
    np->nd_proto_family = PF_NDRV;

	return result;
}