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
typedef  int mbedtls_ecp_group_id ;
struct TYPE_5__ {int id; int /*<<< orphan*/  modp; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;

/* Variables and functions */
 int LOAD_GROUP (int /*<<< orphan*/ ) ; 
 int LOAD_GROUP_A (int /*<<< orphan*/ ) ; 
#define  MBEDTLS_ECP_DP_BP256R1 139 
#define  MBEDTLS_ECP_DP_BP384R1 138 
#define  MBEDTLS_ECP_DP_BP512R1 137 
#define  MBEDTLS_ECP_DP_CURVE25519 136 
#define  MBEDTLS_ECP_DP_SECP192K1 135 
#define  MBEDTLS_ECP_DP_SECP192R1 134 
#define  MBEDTLS_ECP_DP_SECP224K1 133 
#define  MBEDTLS_ECP_DP_SECP224R1 132 
#define  MBEDTLS_ECP_DP_SECP256K1 131 
#define  MBEDTLS_ECP_DP_SECP256R1 130 
#define  MBEDTLS_ECP_DP_SECP384R1 129 
#define  MBEDTLS_ECP_DP_SECP521R1 128 
 int MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE ; 
 int /*<<< orphan*/  NIST_MODP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brainpoolP256r1 ; 
 int /*<<< orphan*/  brainpoolP384r1 ; 
 int /*<<< orphan*/  brainpoolP512r1 ; 
 int /*<<< orphan*/  ecp_mod_p192k1 ; 
 int /*<<< orphan*/  ecp_mod_p224k1 ; 
 int /*<<< orphan*/  ecp_mod_p255 ; 
 int /*<<< orphan*/  ecp_mod_p256k1 ; 
 int ecp_use_curve25519 (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_free (TYPE_1__*) ; 
 int /*<<< orphan*/  p192 ; 
 int /*<<< orphan*/  p224 ; 
 int /*<<< orphan*/  p256 ; 
 int /*<<< orphan*/  p384 ; 
 int /*<<< orphan*/  p521 ; 
 int /*<<< orphan*/  secp192k1 ; 
 int /*<<< orphan*/  secp192r1 ; 
 int /*<<< orphan*/  secp224k1 ; 
 int /*<<< orphan*/  secp224r1 ; 
 int /*<<< orphan*/  secp256k1 ; 
 int /*<<< orphan*/  secp256r1 ; 
 int /*<<< orphan*/  secp384r1 ; 
 int /*<<< orphan*/  secp521r1 ; 

int mbedtls_ecp_group_load( mbedtls_ecp_group *grp, mbedtls_ecp_group_id id )
{
    mbedtls_ecp_group_free( grp );

    grp->id = id;

    switch( id )
    {
#if defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED)
        case MBEDTLS_ECP_DP_SECP192R1:
            NIST_MODP( p192 );
            return( LOAD_GROUP( secp192r1 ) );
#endif /* MBEDTLS_ECP_DP_SECP192R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED)
        case MBEDTLS_ECP_DP_SECP224R1:
            NIST_MODP( p224 );
            return( LOAD_GROUP( secp224r1 ) );
#endif /* MBEDTLS_ECP_DP_SECP224R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED)
        case MBEDTLS_ECP_DP_SECP256R1:
            NIST_MODP( p256 );
            return( LOAD_GROUP( secp256r1 ) );
#endif /* MBEDTLS_ECP_DP_SECP256R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
        case MBEDTLS_ECP_DP_SECP384R1:
            NIST_MODP( p384 );
            return( LOAD_GROUP( secp384r1 ) );
#endif /* MBEDTLS_ECP_DP_SECP384R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
        case MBEDTLS_ECP_DP_SECP521R1:
            NIST_MODP( p521 );
            return( LOAD_GROUP( secp521r1 ) );
#endif /* MBEDTLS_ECP_DP_SECP521R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED)
        case MBEDTLS_ECP_DP_SECP192K1:
            grp->modp = ecp_mod_p192k1;
            return( LOAD_GROUP_A( secp192k1 ) );
#endif /* MBEDTLS_ECP_DP_SECP192K1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED)
        case MBEDTLS_ECP_DP_SECP224K1:
            grp->modp = ecp_mod_p224k1;
            return( LOAD_GROUP_A( secp224k1 ) );
#endif /* MBEDTLS_ECP_DP_SECP224K1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)
        case MBEDTLS_ECP_DP_SECP256K1:
            grp->modp = ecp_mod_p256k1;
            return( LOAD_GROUP_A( secp256k1 ) );
#endif /* MBEDTLS_ECP_DP_SECP256K1_ENABLED */

#if defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
        case MBEDTLS_ECP_DP_BP256R1:
            return( LOAD_GROUP_A( brainpoolP256r1 ) );
#endif /* MBEDTLS_ECP_DP_BP256R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
        case MBEDTLS_ECP_DP_BP384R1:
            return( LOAD_GROUP_A( brainpoolP384r1 ) );
#endif /* MBEDTLS_ECP_DP_BP384R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)
        case MBEDTLS_ECP_DP_BP512R1:
            return( LOAD_GROUP_A( brainpoolP512r1 ) );
#endif /* MBEDTLS_ECP_DP_BP512R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
        case MBEDTLS_ECP_DP_CURVE25519:
            grp->modp = ecp_mod_p255;
            return( ecp_use_curve25519( grp ) );
#endif /* MBEDTLS_ECP_DP_CURVE25519_ENABLED */

        default:
            mbedtls_ecp_group_free( grp );
            return( MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE );
    }
}