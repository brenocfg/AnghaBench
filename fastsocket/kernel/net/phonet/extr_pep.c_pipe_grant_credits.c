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
struct sock {scalar_t__ sk_state; } ;
struct pep_sock {int rx_fc; int rx_credits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CREDITS_MAX ; 
 int CREDITS_THR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PEP_IND_READY ; 
#define  PN_LEGACY_FLOW_CONTROL 130 
#define  PN_MULTI_CREDIT_FLOW_CONTROL 129 
#define  PN_ONE_CREDIT_FLOW_CONTROL 128 
 int /*<<< orphan*/  PN_PEP_IND_FLOW_CONTROL ; 
 int /*<<< orphan*/  PN_PEP_IND_ID_MCFC_GRANT_CREDITS ; 
 scalar_t__ TCP_ESTABLISHED ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  pipe_snd_status (struct sock*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_grant_credits(struct sock *sk)
{
	struct pep_sock *pn = pep_sk(sk);

	BUG_ON(sk->sk_state != TCP_ESTABLISHED);

	switch (pn->rx_fc) {
	case PN_LEGACY_FLOW_CONTROL: /* TODO */
		break;
	case PN_ONE_CREDIT_FLOW_CONTROL:
		pipe_snd_status(sk, PN_PEP_IND_FLOW_CONTROL,
				PEP_IND_READY, GFP_ATOMIC);
		pn->rx_credits = 1;
		break;
	case PN_MULTI_CREDIT_FLOW_CONTROL:
		if ((pn->rx_credits + CREDITS_THR) > CREDITS_MAX)
			break;
		if (pipe_snd_status(sk, PN_PEP_IND_ID_MCFC_GRANT_CREDITS,
					CREDITS_MAX - pn->rx_credits,
					GFP_ATOMIC) == 0)
			pn->rx_credits = CREDITS_MAX;
		break;
	}
}