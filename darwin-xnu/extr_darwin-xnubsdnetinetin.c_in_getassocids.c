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
typedef  scalar_t__ uint32_t ;
struct socket {int dummy; } ;
struct inpcb {scalar_t__ inp_state; } ;
typedef  int /*<<< orphan*/  sae_associd_t ;
typedef  int /*<<< orphan*/  aid ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INPCB_STATE_DEAD ; 
 int /*<<< orphan*/  SAE_ASSOCID_ANY ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
in_getassocids(struct socket *so, uint32_t *cnt, user_addr_t aidp)
{
	struct inpcb *inp = sotoinpcb(so);
	sae_associd_t aid;

	if (inp == NULL || inp->inp_state == INPCB_STATE_DEAD)
		return (EINVAL);

	/* INPCB has no concept of association */
	aid = SAE_ASSOCID_ANY;
	*cnt = 0;

	/* just asking how many there are? */
	if (aidp == USER_ADDR_NULL)
		return (0);

	return (copyout(&aid, aidp, sizeof (aid)));
}