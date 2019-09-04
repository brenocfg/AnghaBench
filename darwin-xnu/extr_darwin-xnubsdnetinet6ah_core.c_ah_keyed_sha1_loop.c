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
struct ah_algorithm_state {scalar_t__ foo; } ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
ah_keyed_sha1_loop(struct ah_algorithm_state *state, caddr_t addr, size_t len)
{
	SHA1_CTX *ctxt;

	if (!state || !state->foo)
		panic("ah_keyed_sha1_loop: what?");
	ctxt = (SHA1_CTX *)state->foo;

	SHA1Update(ctxt, (caddr_t)addr, (size_t)len);
}