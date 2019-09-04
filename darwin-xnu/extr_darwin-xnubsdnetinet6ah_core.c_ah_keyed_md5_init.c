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
typedef  int u_int8_t ;
typedef  int u_int ;
struct secasvar {int /*<<< orphan*/  key_auth; } ;
struct ah_algorithm_state {int /*<<< orphan*/ * foo; struct secasvar* sav; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ _KEYBUF (int /*<<< orphan*/ ) ; 
 int _KEYLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
ah_keyed_md5_init(struct ah_algorithm_state *state, struct secasvar *sav)
{
	size_t padlen;
	size_t keybitlen;
	u_int8_t buf[32] __attribute__((aligned(4)));

	if (!state)
		panic("ah_keyed_md5_init: what?");

	state->sav = sav;
	state->foo = (void *)_MALLOC(sizeof(MD5_CTX), M_TEMP, M_NOWAIT);
	if (state->foo == NULL)
		return ENOBUFS;

	MD5Init((MD5_CTX *)state->foo);
	if (state->sav) {
		MD5Update((MD5_CTX *)state->foo,
			(u_int8_t *)_KEYBUF(state->sav->key_auth),
			(u_int)_KEYLEN(state->sav->key_auth));

		/*
		 * Pad after the key.
		 * We cannot simply use md5_pad() since the function
		 * won't update the total length.
		 */
		if (_KEYLEN(state->sav->key_auth) < 56)
			padlen = 64 - 8 - _KEYLEN(state->sav->key_auth);
		else
			padlen = 64 + 64 - 8 - _KEYLEN(state->sav->key_auth);
		keybitlen = _KEYLEN(state->sav->key_auth);
		keybitlen *= 8;

		buf[0] = 0x80;
		MD5Update((MD5_CTX *)state->foo, &buf[0], 1);
		padlen--;

		bzero(buf, sizeof(buf));
		while (sizeof(buf) < padlen) {
			MD5Update((MD5_CTX *)state->foo, &buf[0], sizeof(buf));
			padlen -= sizeof(buf);
		}
		if (padlen) {
			MD5Update((MD5_CTX *)state->foo, &buf[0], padlen);
		}

		buf[0] = (keybitlen >> 0) & 0xff;
		buf[1] = (keybitlen >> 8) & 0xff;
		buf[2] = (keybitlen >> 16) & 0xff;
		buf[3] = (keybitlen >> 24) & 0xff;
		MD5Update((MD5_CTX *)state->foo, buf, 8);
	}

	return 0;
}