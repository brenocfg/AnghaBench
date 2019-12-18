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
struct ppp_mppe_state {unsigned char* master_key; unsigned char* session_key; int /*<<< orphan*/ * arc4; int /*<<< orphan*/ * sha1; struct ppp_mppe_state* sha1_digest; } ;

/* Variables and functions */
 int CILEN_MPPE ; 
 unsigned char CI_MPPE ; 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 unsigned int MPPE_MAX_KEY_LEN ; 
 int /*<<< orphan*/ * crypto_alloc_blkcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * crypto_alloc_hash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_blkcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_hash (int /*<<< orphan*/ *) ; 
 unsigned int crypto_hash_digestsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ppp_mppe_state*) ; 
 struct ppp_mppe_state* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 struct ppp_mppe_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void *mppe_alloc(unsigned char *options, int optlen)
{
	struct ppp_mppe_state *state;
	unsigned int digestsize;

	if (optlen != CILEN_MPPE + sizeof(state->master_key)
	    || options[0] != CI_MPPE || options[1] != CILEN_MPPE)
		goto out;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		goto out;


	state->arc4 = crypto_alloc_blkcipher("ecb(arc4)", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(state->arc4)) {
		state->arc4 = NULL;
		goto out_free;
	}

	state->sha1 = crypto_alloc_hash("sha1", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(state->sha1)) {
		state->sha1 = NULL;
		goto out_free;
	}

	digestsize = crypto_hash_digestsize(state->sha1);
	if (digestsize < MPPE_MAX_KEY_LEN)
		goto out_free;

	state->sha1_digest = kmalloc(digestsize, GFP_KERNEL);
	if (!state->sha1_digest)
		goto out_free;

	/* Save keys. */
	memcpy(state->master_key, &options[CILEN_MPPE],
	       sizeof(state->master_key));
	memcpy(state->session_key, state->master_key,
	       sizeof(state->master_key));

	/*
	 * We defer initial key generation until mppe_init(), as mppe_alloc()
	 * is called frequently during negotiation.
	 */

	return (void *)state;

	out_free:
	    if (state->sha1_digest)
		kfree(state->sha1_digest);
	    if (state->sha1)
		crypto_free_hash(state->sha1);
	    if (state->arc4)
		crypto_free_blkcipher(state->arc4);
	    kfree(state);
	out:
	return NULL;
}