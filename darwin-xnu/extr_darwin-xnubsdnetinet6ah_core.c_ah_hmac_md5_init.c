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
typedef  int u_char ;
struct secasvar {int /*<<< orphan*/  key_auth; } ;
struct ah_algorithm_state {struct secasvar* sav; void* foo; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  MD5Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int* _KEYBUF (int /*<<< orphan*/ ) ; 
 int _KEYLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int*,int*,size_t) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
ah_hmac_md5_init(struct ah_algorithm_state *state, struct secasvar *sav)
{
	u_char *ipad;
	u_char *opad;
	u_char tk[16] __attribute__((aligned(4)));
	u_char *key;
	size_t keylen;
	size_t i;
	MD5_CTX *ctxt;

	if (!state)
		panic("ah_hmac_md5_init: what?");

	state->sav = sav;
	state->foo = (void *)_MALLOC(64 + 64 + sizeof(MD5_CTX), M_TEMP, M_NOWAIT);
	if (!state->foo)
		return ENOBUFS;

	ipad = (u_char *)state->foo;
	opad = (u_char *)(ipad + 64);
	ctxt = (MD5_CTX *)(void *)(opad + 64);

	/* compress the key if necessery */
	if (64 < _KEYLEN(state->sav->key_auth)) {
		MD5Init(ctxt);
		MD5Update(ctxt, _KEYBUF(state->sav->key_auth),
			_KEYLEN(state->sav->key_auth));
		MD5Final(&tk[0], ctxt);
		key = &tk[0];
		keylen = 16;
	} else {
		key = (u_char *) _KEYBUF(state->sav->key_auth);
		keylen = _KEYLEN(state->sav->key_auth);
	}

	bzero(ipad, 64);
	bzero(opad, 64);
	bcopy(key, ipad, keylen);
	bcopy(key, opad, keylen);
	for (i = 0; i < 64; i++) {
		ipad[i] ^= 0x36;
		opad[i] ^= 0x5c;
	}

	MD5Init(ctxt);
	MD5Update(ctxt, ipad, 64);

	return 0;
}