#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  d; int /*<<< orphan*/  grp; } ;
typedef  TYPE_1__ mbedtls_ecdsa_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecdsa_signature_to_asn1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  mbedtls_ecdsa_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,size_t,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_ecdsa_sign_det (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 

int mbedtls_ecdsa_write_signature( mbedtls_ecdsa_context *ctx, mbedtls_md_type_t md_alg,
                           const unsigned char *hash, size_t hlen,
                           unsigned char *sig, size_t *slen,
                           int (*f_rng)(void *, unsigned char *, size_t),
                           void *p_rng )
{
    int ret;
    mbedtls_mpi r, s;

    mbedtls_mpi_init( &r );
    mbedtls_mpi_init( &s );

#if defined(MBEDTLS_ECDSA_DETERMINISTIC)
    (void) f_rng;
    (void) p_rng;

    MBEDTLS_MPI_CHK( mbedtls_ecdsa_sign_det( &ctx->grp, &r, &s, &ctx->d,
                             hash, hlen, md_alg ) );
#else
    (void) md_alg;

    MBEDTLS_MPI_CHK( mbedtls_ecdsa_sign( &ctx->grp, &r, &s, &ctx->d,
                         hash, hlen, f_rng, p_rng ) );
#endif

    MBEDTLS_MPI_CHK( ecdsa_signature_to_asn1( &r, &s, sig, slen ) );

cleanup:
    mbedtls_mpi_free( &r );
    mbedtls_mpi_free( &s );

    return( ret );
}