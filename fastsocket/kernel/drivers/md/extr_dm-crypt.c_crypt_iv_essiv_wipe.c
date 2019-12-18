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
struct iv_essiv_private {int /*<<< orphan*/  salt; int /*<<< orphan*/  tfm; int /*<<< orphan*/  hash_tfm; } ;
struct TYPE_2__ {struct iv_essiv_private essiv; } ;
struct crypt_config {TYPE_1__ iv_gen_private; } ;

/* Variables and functions */
 int crypto_cipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int crypto_hash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int crypt_iv_essiv_wipe(struct crypt_config *cc)
{
	struct iv_essiv_private *essiv = &cc->iv_gen_private.essiv;
	unsigned salt_size = crypto_hash_digestsize(essiv->hash_tfm);

	memset(essiv->salt, 0, salt_size);

	return crypto_cipher_setkey(essiv->tfm, essiv->salt, salt_size);
}