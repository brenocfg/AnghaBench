#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ grp; } ;
typedef  TYPE_2__ mbedtls_ecp_keypair ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_oid (unsigned char**,unsigned char*,char const*,size_t) ; 
 int mbedtls_oid_get_oid_by_ec_grp (int /*<<< orphan*/ ,char const**,size_t*) ; 

__attribute__((used)) static int pk_write_ec_param( unsigned char **p, unsigned char *start,
                                mbedtls_ecp_keypair *ec )
{
    int ret;
    size_t len = 0;
    const char *oid;
    size_t oid_len;

    if( ( ret = mbedtls_oid_get_oid_by_ec_grp( ec->grp.id, &oid, &oid_len ) ) != 0 )
        return( ret );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_oid( p, start, oid, oid_len ) );

    return( (int) len );
}