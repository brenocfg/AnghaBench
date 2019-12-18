#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tag; scalar_t__ len; } ;
typedef  TYPE_1__ mbedtls_x509_buf ;
typedef  scalar_t__ mbedtls_pk_type_t ;
struct TYPE_10__ {int /*<<< orphan*/  expected_salt_len; int /*<<< orphan*/  mgf1_hash_id; } ;
typedef  TYPE_2__ mbedtls_pk_rsassa_pss_options ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;

/* Variables and functions */
 scalar_t__ MBEDTLS_ASN1_NULL ; 
 int MBEDTLS_ERR_X509_ALLOC_FAILED ; 
 int MBEDTLS_ERR_X509_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_X509_INVALID_ALG ; 
 int MBEDTLS_ERR_X509_UNKNOWN_SIG_ALG ; 
 scalar_t__ MBEDTLS_PK_RSASSA_PSS ; 
 TYPE_2__* mbedtls_calloc (int,int) ; 
 int /*<<< orphan*/  mbedtls_free (TYPE_2__*) ; 
 int mbedtls_oid_get_sig_alg (TYPE_1__ const*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int mbedtls_x509_get_rsassa_pss_params (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mbedtls_x509_get_sig_alg( const mbedtls_x509_buf *sig_oid, const mbedtls_x509_buf *sig_params,
                      mbedtls_md_type_t *md_alg, mbedtls_pk_type_t *pk_alg,
                      void **sig_opts )
{
    int ret;

    if( *sig_opts != NULL )
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );

    if( ( ret = mbedtls_oid_get_sig_alg( sig_oid, md_alg, pk_alg ) ) != 0 )
        return( MBEDTLS_ERR_X509_UNKNOWN_SIG_ALG + ret );

#if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT)
    if( *pk_alg == MBEDTLS_PK_RSASSA_PSS )
    {
        mbedtls_pk_rsassa_pss_options *pss_opts;

        pss_opts = mbedtls_calloc( 1, sizeof( mbedtls_pk_rsassa_pss_options ) );
        if( pss_opts == NULL )
            return( MBEDTLS_ERR_X509_ALLOC_FAILED );

        ret = mbedtls_x509_get_rsassa_pss_params( sig_params,
                                          md_alg,
                                          &pss_opts->mgf1_hash_id,
                                          &pss_opts->expected_salt_len );
        if( ret != 0 )
        {
            mbedtls_free( pss_opts );
            return( ret );
        }

        *sig_opts = (void *) pss_opts;
    }
    else
#endif /* MBEDTLS_X509_RSASSA_PSS_SUPPORT */
    {
        /* Make sure parameters are absent or NULL */
        if( ( sig_params->tag != MBEDTLS_ASN1_NULL && sig_params->tag != 0 ) ||
              sig_params->len != 0 )
        return( MBEDTLS_ERR_X509_INVALID_ALG );
    }

    return( 0 );
}