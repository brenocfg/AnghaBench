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
typedef  int /*<<< orphan*/  u8 ;
struct crypt_config {int key_size; int /*<<< orphan*/  key; int /*<<< orphan*/  tfm; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CRYPT_KEY_VALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int crypto_ablkcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int crypt_wipe_key(struct crypt_config *cc)
{
	clear_bit(DM_CRYPT_KEY_VALID, &cc->flags);
	memset(&cc->key, 0, cc->key_size * sizeof(u8));
	return crypto_ablkcipher_setkey(cc->tfm, cc->key, cc->key_size);
}