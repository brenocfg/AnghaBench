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
struct pf_state_key {int /*<<< orphan*/  flowhash; int /*<<< orphan*/  flowsrc; int /*<<< orphan*/ * app_state; int /*<<< orphan*/  proto_variant; int /*<<< orphan*/  direction; int /*<<< orphan*/  proto; int /*<<< orphan*/  af_gwy; int /*<<< orphan*/  af_lan; int /*<<< orphan*/  ext_gwy; int /*<<< orphan*/  ext_lan; int /*<<< orphan*/  gwy; int /*<<< orphan*/  lan; int /*<<< orphan*/  states; } ;
struct pf_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PR_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct pf_state_key*,int) ; 
 int /*<<< orphan*/  pf_attach_state (struct pf_state_key*,struct pf_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_state_key_pl ; 
 struct pf_state_key* pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct pf_state_key *
pf_alloc_state_key(struct pf_state *s, struct pf_state_key *psk)
{
	struct pf_state_key	*sk;

	if ((sk = pool_get(&pf_state_key_pl, PR_WAITOK)) == NULL)
		return (NULL);
	bzero(sk, sizeof (*sk));
	TAILQ_INIT(&sk->states);
	pf_attach_state(sk, s, 0);

	/* initialize state key from psk, if provided */
	if (psk != NULL) {
		bcopy(&psk->lan, &sk->lan, sizeof (sk->lan));
		bcopy(&psk->gwy, &sk->gwy, sizeof (sk->gwy));
		bcopy(&psk->ext_lan, &sk->ext_lan, sizeof (sk->ext_lan));
		bcopy(&psk->ext_gwy, &sk->ext_gwy, sizeof (sk->ext_gwy));
		sk->af_lan = psk->af_lan;
		sk->af_gwy = psk->af_gwy;
		sk->proto = psk->proto;
		sk->direction = psk->direction;
		sk->proto_variant = psk->proto_variant;
		VERIFY(psk->app_state == NULL);
		sk->flowsrc = psk->flowsrc;
		sk->flowhash = psk->flowhash;
		/* don't touch tree entries, states and refcnt on sk */
	}

	return (sk);
}