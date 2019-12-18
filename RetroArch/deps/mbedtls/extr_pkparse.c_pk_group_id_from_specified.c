#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_ecp_group_id ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group ;
typedef  int /*<<< orphan*/  mbedtls_asn1_buf ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_ecp_group_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_init (int /*<<< orphan*/ *) ; 
 int pk_group_from_specified (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int pk_group_id_from_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pk_group_id_from_specified( const mbedtls_asn1_buf *params,
                                       mbedtls_ecp_group_id *grp_id )
{
    int ret;
    mbedtls_ecp_group grp;

    mbedtls_ecp_group_init( &grp );

    if( ( ret = pk_group_from_specified( params, &grp ) ) != 0 )
        goto cleanup;

    ret = pk_group_id_from_group( &grp, grp_id );

cleanup:
    mbedtls_ecp_group_free( &grp );

    return( ret );
}