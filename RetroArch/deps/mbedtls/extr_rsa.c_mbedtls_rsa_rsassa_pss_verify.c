#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hash_id; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;

/* Variables and functions */
 scalar_t__ MBEDTLS_MD_NONE ; 
 int /*<<< orphan*/  MBEDTLS_RSA_SALT_LEN_ANY ; 
 int mbedtls_rsa_rsassa_pss_verify_ext (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*,int,int /*<<< orphan*/ ,unsigned int,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*) ; 

int mbedtls_rsa_rsassa_pss_verify( mbedtls_rsa_context *ctx,
                           int (*f_rng)(void *, unsigned char *, size_t),
                           void *p_rng,
                           int mode,
                           mbedtls_md_type_t md_alg,
                           unsigned int hashlen,
                           const unsigned char *hash,
                           const unsigned char *sig )
{
    mbedtls_md_type_t mgf1_hash_id = ( ctx->hash_id != MBEDTLS_MD_NONE )
                             ? (mbedtls_md_type_t) ctx->hash_id
                             : md_alg;

    return( mbedtls_rsa_rsassa_pss_verify_ext( ctx, f_rng, p_rng, mode,
                                       md_alg, hashlen, hash,
                                       mgf1_hash_id, MBEDTLS_RSA_SALT_LEN_ANY,
                                       sig ) );

}