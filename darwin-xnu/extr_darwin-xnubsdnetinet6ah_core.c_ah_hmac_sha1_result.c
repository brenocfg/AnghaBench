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
typedef  int /*<<< orphan*/  u_char ;
struct ah_algorithm_state {scalar_t__ foo; } ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/ * caddr_t ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  SHA1Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int SHA1_RESULTLEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
ah_hmac_sha1_result(struct ah_algorithm_state *state, caddr_t addr, size_t l)
{
	u_char digest[SHA1_RESULTLEN] __attribute__((aligned(4)));	/* SHA-1 generates 160 bits */
	u_char *ipad;
	u_char *opad;
	SHA1_CTX *ctxt;

	if (!state || !state->foo)
		panic("ah_hmac_sha1_result: what?");

	ipad = (u_char *)state->foo;
	opad = (u_char *)(ipad + 64);
	ctxt = (SHA1_CTX *)(void *)(opad + 64);

	SHA1Final((caddr_t)&digest[0], ctxt);

	SHA1Init(ctxt);
	SHA1Update(ctxt, opad, 64);
	SHA1Update(ctxt, (caddr_t)&digest[0], sizeof(digest));
	SHA1Final((caddr_t)&digest[0], ctxt);

	bcopy(&digest[0], (void *)addr, sizeof(digest) > l ? l : sizeof(digest));

	FREE(state->foo, M_TEMP);
}