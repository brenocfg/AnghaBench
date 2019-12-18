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
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int SERPENT_MAX_KEY_SIZE ; 
 int serpent_setkey (struct crypto_tfm*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int tnepres_setkey(struct crypto_tfm *tfm, const u8 *key,
			  unsigned int keylen)
{
	u8 rev_key[SERPENT_MAX_KEY_SIZE];
	int i;

	for (i = 0; i < keylen; ++i)
		rev_key[keylen - i - 1] = key[i];
 
	return serpent_setkey(tfm, rev_key, keylen);
}