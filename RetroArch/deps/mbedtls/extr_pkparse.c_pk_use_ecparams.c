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
typedef  scalar_t__ mbedtls_ecp_group_id ;
struct TYPE_8__ {scalar_t__ id; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;
struct TYPE_9__ {scalar_t__ tag; } ;
typedef  TYPE_2__ mbedtls_asn1_buf ;

/* Variables and functions */
 scalar_t__ MBEDTLS_ASN1_OID ; 
 scalar_t__ MBEDTLS_ECP_DP_NONE ; 
 int MBEDTLS_ERR_PK_KEY_INVALID_FORMAT ; 
 int MBEDTLS_ERR_PK_UNKNOWN_NAMED_CURVE ; 
 int mbedtls_ecp_group_load (TYPE_1__*,scalar_t__) ; 
 scalar_t__ mbedtls_oid_get_ec_grp (TYPE_2__ const*,scalar_t__*) ; 
 int pk_group_id_from_specified (TYPE_2__ const*,scalar_t__*) ; 

__attribute__((used)) static int pk_use_ecparams( const mbedtls_asn1_buf *params, mbedtls_ecp_group *grp )
{
    int ret;
    mbedtls_ecp_group_id grp_id;

    if( params->tag == MBEDTLS_ASN1_OID )
    {
        if( mbedtls_oid_get_ec_grp( params, &grp_id ) != 0 )
            return( MBEDTLS_ERR_PK_UNKNOWN_NAMED_CURVE );
    }
    else
    {
#if defined(MBEDTLS_PK_PARSE_EC_EXTENDED)
        if( ( ret = pk_group_id_from_specified( params, &grp_id ) ) != 0 )
            return( ret );
#else
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT );
#endif
    }

    /*
     * grp may already be initilialized; if so, make sure IDs match
     */
    if( grp->id != MBEDTLS_ECP_DP_NONE && grp->id != grp_id )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT );

    if( ( ret = mbedtls_ecp_group_load( grp, grp_id ) ) != 0 )
        return( ret );

    return( 0 );
}