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
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
ah_hmac_md5_result(struct ah_algorithm_state *state, caddr_t addr, size_t l)
{
	u_char digest[16] __attribute__((aligned(4)));
	u_char *ipad;
	u_char *opad;
	MD5_CTX *ctxt;

	if (!state || !state->foo)
		panic("ah_hmac_md5_result: what?");

	ipad = (u_char *)state->foo;
	opad = (u_char *)(ipad + 64);
	ctxt = (MD5_CTX *)(void *)(opad + 64);

	MD5Final(&digest[0], ctxt);

	MD5Init(ctxt);
	MD5Update(ctxt, opad, 64);
	MD5Update(ctxt, &digest[0], sizeof(digest));
	MD5Final(&digest[0], ctxt);

	bcopy(&digest[0], (void *)addr, sizeof(digest) > l ? l : sizeof(digest));

	FREE(state->foo, M_TEMP);
}