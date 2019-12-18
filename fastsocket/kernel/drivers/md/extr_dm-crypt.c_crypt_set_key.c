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
struct crypt_config {int key_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  key; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CRYPT_KEY_VALID ; 
 int EINVAL ; 
 scalar_t__ crypt_decode_key (int /*<<< orphan*/ ,char*,int) ; 
 int crypto_ablkcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int crypt_set_key(struct crypt_config *cc, char *key)
{
	int r = -EINVAL;
	int key_string_len = strlen(key);

	/* The key size may not be changed. */
	if (cc->key_size != (key_string_len >> 1))
		goto out;

	/* Hyphen (which gives a key_size of zero) means there is no key. */
	if (!cc->key_size && strcmp(key, "-"))
		goto out;

	if (cc->key_size && crypt_decode_key(cc->key, key, cc->key_size) < 0)
		goto out;

	r = crypto_ablkcipher_setkey(cc->tfm, cc->key, cc->key_size);
	if (!r)
		set_bit(DM_CRYPT_KEY_VALID, &cc->flags);
out:
	/* Hex key string not needed after here, so wipe it. */
	memset(key, '0', key_string_len);

	return r;
}