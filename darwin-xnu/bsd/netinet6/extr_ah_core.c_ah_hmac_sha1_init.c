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
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  SHA1Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int*,int) ; 
 int SHA1_RESULTLEN ; 
 int* _KEYBUF (int /*<<< orphan*/ ) ; 
 int _KEYLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int*,int*,size_t) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
ah_hmac_sha1_init(struct ah_algorithm_state *state, struct secasvar *sav)
{
	u_char *ipad;
	u_char *opad;
	SHA1_CTX *ctxt;
	u_char tk[SHA1_RESULTLEN] __attribute__((aligned(4)));	/* SHA-1 generates 160 bits */
	u_char *key;
	size_t keylen;
	size_t i;

	if (!state)
		panic("ah_hmac_sha1_init: what?");

	state->sav = sav;
	state->foo = (void *)_MALLOC(64 + 64 + sizeof(SHA1_CTX),
			M_TEMP, M_NOWAIT);
	if (!state->foo)
		return ENOBUFS;

	ipad = (u_char *)state->foo;
	opad = (u_char *)(ipad + 64);
	ctxt = (SHA1_CTX *)(void *)(opad + 64);

	/* compress the key if necessery */
	if (64 < _KEYLEN(state->sav->key_auth)) {
		SHA1Init(ctxt);
		SHA1Update(ctxt, _KEYBUF(state->sav->key_auth),
			_KEYLEN(state->sav->key_auth));
		SHA1Final(&tk[0], ctxt);
		key = &tk[0];
		keylen = SHA1_RESULTLEN;
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

	SHA1Init(ctxt);
	SHA1Update(ctxt, ipad, 64);

	return 0;
}