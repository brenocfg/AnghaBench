#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int padding; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;

/* Variables and functions */
 int MBEDTLS_ERR_RSA_INVALID_PADDING ; 
#define  MBEDTLS_RSA_PKCS_V15 129 
#define  MBEDTLS_RSA_PKCS_V21 128 
 int mbedtls_rsa_rsassa_pkcs1_v15_verify (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*,int,int /*<<< orphan*/ ,unsigned int,unsigned char const*,unsigned char const*) ; 
 int mbedtls_rsa_rsassa_pss_verify (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*,int,int /*<<< orphan*/ ,unsigned int,unsigned char const*,unsigned char const*) ; 

int mbedtls_rsa_pkcs1_verify( mbedtls_rsa_context *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng,
                      int mode,
                      mbedtls_md_type_t md_alg,
                      unsigned int hashlen,
                      const unsigned char *hash,
                      const unsigned char *sig )
{
    switch( ctx->padding )
    {
#if defined(MBEDTLS_PKCS1_V15)
        case MBEDTLS_RSA_PKCS_V15:
            return mbedtls_rsa_rsassa_pkcs1_v15_verify( ctx, f_rng, p_rng, mode, md_alg,
                                                hashlen, hash, sig );
#endif

#if defined(MBEDTLS_PKCS1_V21)
        case MBEDTLS_RSA_PKCS_V21:
            return mbedtls_rsa_rsassa_pss_verify( ctx, f_rng, p_rng, mode, md_alg,
                                          hashlen, hash, sig );
#endif

        default:
            return( MBEDTLS_ERR_RSA_INVALID_PADDING );
    }
}