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
struct crypto_aead {int dummy; } ;
struct aead_givcrypt_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ PTR_ALIGN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_givcrypt_set_tfm (struct aead_givcrypt_request*,struct crypto_aead*) ; 
 int crypto_aead_ivsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_tfm_ctx_alignment () ; 

__attribute__((used)) static inline struct aead_givcrypt_request *esp_tmp_givreq(
	struct crypto_aead *aead, u8 *iv)
{
	struct aead_givcrypt_request *req;

	req = (void *)PTR_ALIGN(iv + crypto_aead_ivsize(aead),
				crypto_tfm_ctx_alignment());
	aead_givcrypt_set_tfm(req, aead);
	return req;
}