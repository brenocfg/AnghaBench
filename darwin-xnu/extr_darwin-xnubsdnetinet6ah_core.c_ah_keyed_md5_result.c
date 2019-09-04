#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ah_algorithm_state {scalar_t__ foo; TYPE_1__* sav; } ;
typedef  int /*<<< orphan*/  digest ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  key_auth; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ _KEYBUF (int /*<<< orphan*/ ) ; 
 scalar_t__ _KEYLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
ah_keyed_md5_result(struct ah_algorithm_state *state, caddr_t addr, size_t l)
{
	u_char digest[16] __attribute__((aligned(4)));

	if (!state)
		panic("ah_keyed_md5_result: what?");

	if (state->sav) {
		MD5Update((MD5_CTX *)state->foo,
			(u_int8_t *)_KEYBUF(state->sav->key_auth),
			(u_int)_KEYLEN(state->sav->key_auth));
	}
	MD5Final(&digest[0], (MD5_CTX *)state->foo);
	FREE(state->foo, M_TEMP);
	bcopy(&digest[0], (void *)addr, sizeof(digest) > l ? l : sizeof(digest));
}