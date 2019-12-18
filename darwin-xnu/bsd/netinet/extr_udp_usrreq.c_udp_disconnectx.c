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
struct socket {int dummy; } ;
typedef  int /*<<< orphan*/  sae_connid_t ;
typedef  scalar_t__ sae_associd_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SAE_ASSOCID_ALL ; 
 scalar_t__ SAE_ASSOCID_ANY ; 
 int udp_disconnect (struct socket*) ; 

int
udp_disconnectx(struct socket *so, sae_associd_t aid, sae_connid_t cid)
{
#pragma unused(cid)
	if (aid != SAE_ASSOCID_ANY && aid != SAE_ASSOCID_ALL)
		return (EINVAL);

	return (udp_disconnect(so));
}