#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_aead {int dummy; } ;
struct TYPE_4__ {unsigned int maxauthsize; } ;
struct TYPE_3__ {unsigned int authsize; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* crypto_aead_alg (struct crypto_aead*) ; 
 TYPE_1__* crypto_aead_crt (struct crypto_aead*) ; 

__attribute__((used)) static int gcm_aes_nx_setauthsize(struct crypto_aead *tfm,
				  unsigned int authsize)
{
	if (authsize > crypto_aead_alg(tfm)->maxauthsize)
		return -EINVAL;

	crypto_aead_crt(tfm)->authsize = authsize;

	return 0;
}