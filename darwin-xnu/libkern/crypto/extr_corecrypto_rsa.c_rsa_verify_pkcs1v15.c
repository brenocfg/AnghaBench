#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ rsa_pub_ctx ;
struct TYPE_5__ {int (* ccrsa_verify_pkcs1v15_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int*) ;} ;

/* Variables and functions */
 TYPE_3__* g_crypto_funcs ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int*) ; 

int rsa_verify_pkcs1v15(rsa_pub_ctx *pub, const uint8_t *oid,
                          size_t digest_len, const uint8_t *digest,
                          size_t sig_len, const uint8_t *sig,
                          bool *valid) {
	return g_crypto_funcs->ccrsa_verify_pkcs1v15_fn(pub->key,oid,
			digest_len,digest,
			sig_len,sig,valid);
}