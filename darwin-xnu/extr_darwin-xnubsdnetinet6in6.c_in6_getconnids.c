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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint32_t ;
struct socket {int so_state; } ;
struct in6pcb {scalar_t__ inp_state; } ;
typedef  int sae_connid_t ;
typedef  scalar_t__ sae_associd_t ;
typedef  int /*<<< orphan*/  cid ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INPCB_STATE_DEAD ; 
 scalar_t__ SAE_ASSOCID_ALL ; 
 scalar_t__ SAE_ASSOCID_ANY ; 
 int SAE_CONNID_ANY ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 struct in6pcb* sotoin6pcb (struct socket*) ; 

__attribute__((used)) static int
in6_getconnids(struct socket *so, sae_associd_t aid, uint32_t *cnt,
    user_addr_t cidp)
{
	struct in6pcb *in6p = sotoin6pcb(so);
	sae_connid_t cid;

	if (in6p == NULL || in6p->inp_state == INPCB_STATE_DEAD)
		return (EINVAL);

	if (aid != SAE_ASSOCID_ANY && aid != SAE_ASSOCID_ALL)
		return (EINVAL);

	/* if connected, return 1 connection count */
	*cnt = ((so->so_state & SS_ISCONNECTED) ? 1 : 0);

	/* just asking how many there are? */
	if (cidp == USER_ADDR_NULL)
		return (0);

	/* if IN6PCB is connected, assign it connid 1 */
	cid = ((*cnt != 0) ? 1 : SAE_CONNID_ANY);

	return (copyout(&cid, cidp, sizeof (cid)));
}