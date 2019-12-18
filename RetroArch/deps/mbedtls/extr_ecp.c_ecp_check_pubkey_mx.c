#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_6__ {int nbits; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_INVALID_KEY ; 
 int mbedtls_mpi_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecp_check_pubkey_mx( const mbedtls_ecp_group *grp, const mbedtls_ecp_point *pt )
{
    /* [Curve25519 p. 5] Just check X is the correct number of bytes */
    if( mbedtls_mpi_size( &pt->X ) > ( grp->nbits + 7 ) / 8 )
        return( MBEDTLS_ERR_ECP_INVALID_KEY );

    return( 0 );
}