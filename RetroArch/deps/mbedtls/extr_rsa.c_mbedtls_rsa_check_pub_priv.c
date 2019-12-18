#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  E; int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;

/* Variables and functions */
 int MBEDTLS_ERR_RSA_KEY_CHECK_FAILED ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_rsa_check_privkey (TYPE_1__ const*) ; 
 scalar_t__ mbedtls_rsa_check_pubkey (TYPE_1__ const*) ; 

int mbedtls_rsa_check_pub_priv( const mbedtls_rsa_context *pub, const mbedtls_rsa_context *prv )
{
    if( mbedtls_rsa_check_pubkey( pub ) != 0 ||
        mbedtls_rsa_check_privkey( prv ) != 0 )
    {
        return( MBEDTLS_ERR_RSA_KEY_CHECK_FAILED );
    }

    if( mbedtls_mpi_cmp_mpi( &pub->N, &prv->N ) != 0 ||
        mbedtls_mpi_cmp_mpi( &pub->E, &prv->E ) != 0 )
    {
        return( MBEDTLS_ERR_RSA_KEY_CHECK_FAILED );
    }

    return( 0 );
}