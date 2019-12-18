#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mbedtls_pk_type_t ;
struct TYPE_8__ {int /*<<< orphan*/  expected_salt_len; int /*<<< orphan*/  mgf1_hash_id; } ;
typedef  TYPE_1__ mbedtls_pk_rsassa_pss_options ;
struct TYPE_9__ {int /*<<< orphan*/ * pk_info; } ;
typedef  TYPE_2__ mbedtls_pk_context ;
typedef  scalar_t__ mbedtls_md_type_t ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_PK_SIG_LEN_MISMATCH ; 
 int MBEDTLS_ERR_PK_TYPE_MISMATCH ; 
 int MBEDTLS_ERR_RSA_VERIFY_FAILED ; 
 scalar_t__ MBEDTLS_MD_NONE ; 
 scalar_t__ MBEDTLS_PK_RSASSA_PSS ; 
 int /*<<< orphan*/  MBEDTLS_RSA_PUBLIC ; 
 size_t UINT_MAX ; 
 int /*<<< orphan*/  mbedtls_pk_can_do (TYPE_2__*,scalar_t__) ; 
 size_t mbedtls_pk_get_len (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_pk_rsa (TYPE_2__) ; 
 int mbedtls_pk_verify (TYPE_2__*,scalar_t__,unsigned char const*,size_t,unsigned char const*,size_t) ; 
 int mbedtls_rsa_rsassa_pss_verify_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*) ; 

int mbedtls_pk_verify_ext( mbedtls_pk_type_t type, const void *options,
                   mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   const unsigned char *sig, size_t sig_len )
{
    if( ctx == NULL || ctx->pk_info == NULL )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    if( ! mbedtls_pk_can_do( ctx, type ) )
        return( MBEDTLS_ERR_PK_TYPE_MISMATCH );

    if( type == MBEDTLS_PK_RSASSA_PSS )
    {
#if defined(MBEDTLS_RSA_C) && defined(MBEDTLS_PKCS1_V21)
        int ret;
        const mbedtls_pk_rsassa_pss_options *pss_opts;

#if defined(MBEDTLS_HAVE_INT64)
        if( md_alg == MBEDTLS_MD_NONE && UINT_MAX < hash_len )
            return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
#endif /* MBEDTLS_HAVE_INT64 */

        if( options == NULL )
            return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

        pss_opts = (const mbedtls_pk_rsassa_pss_options *) options;

        if( sig_len < mbedtls_pk_get_len( ctx ) )
            return( MBEDTLS_ERR_RSA_VERIFY_FAILED );

        ret = mbedtls_rsa_rsassa_pss_verify_ext( mbedtls_pk_rsa( *ctx ),
                NULL, NULL, MBEDTLS_RSA_PUBLIC,
                md_alg, (unsigned int) hash_len, hash,
                pss_opts->mgf1_hash_id,
                pss_opts->expected_salt_len,
                sig );
        if( ret != 0 )
            return( ret );

        if( sig_len > mbedtls_pk_get_len( ctx ) )
            return( MBEDTLS_ERR_PK_SIG_LEN_MISMATCH );

        return( 0 );
#else
        return( MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE );
#endif /* MBEDTLS_RSA_C && MBEDTLS_PKCS1_V21 */
    }

    /* General case: no options */
    if( options != NULL )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    return( mbedtls_pk_verify( ctx, md_alg, hash, hash_len, sig, sig_len ) );
}