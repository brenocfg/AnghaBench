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
struct ppp_mppe_state {scalar_t__ arc4; scalar_t__ sha1; struct ppp_mppe_state* sha1_digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_blkcipher (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_hash (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ppp_mppe_state*) ; 

__attribute__((used)) static void mppe_free(void *arg)
{
	struct ppp_mppe_state *state = (struct ppp_mppe_state *) arg;
	if (state) {
	    if (state->sha1_digest)
		kfree(state->sha1_digest);
	    if (state->sha1)
		crypto_free_hash(state->sha1);
	    if (state->arc4)
		crypto_free_blkcipher(state->arc4);
	    kfree(state);
	}
}