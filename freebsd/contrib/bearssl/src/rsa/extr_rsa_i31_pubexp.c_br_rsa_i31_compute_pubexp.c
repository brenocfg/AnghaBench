#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  dqlen; int /*<<< orphan*/  dq; int /*<<< orphan*/  qlen; int /*<<< orphan*/  q; int /*<<< orphan*/  dplen; int /*<<< orphan*/  dp; int /*<<< orphan*/  plen; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ br_rsa_private_key ;

/* Variables and functions */
 int EQ (int,int) ; 
 int get_pubexp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t
br_rsa_i31_compute_pubexp(const br_rsa_private_key *sk)
{
	/*
	 * Get the public exponent from both p and q. This is the right
	 * exponent if we get twice the same value.
	 */
	uint32_t ep, eq;

	ep = get_pubexp(sk->p, sk->plen, sk->dp, sk->dplen);
	eq = get_pubexp(sk->q, sk->qlen, sk->dq, sk->dqlen);
	return ep & -EQ(ep, eq);
}