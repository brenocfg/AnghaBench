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
struct TYPE_3__ {int /*<<< orphan*/  Q; int /*<<< orphan*/  grp; } ;
typedef  TYPE_1__ mbedtls_ecp_keypair ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MBEDTLS_ECP_MAX_PT_LEN ; 
 int /*<<< orphan*/  MBEDTLS_ECP_PF_UNCOMPRESSED ; 
 int MBEDTLS_ERR_ASN1_BUF_TOO_SMALL ; 
 int mbedtls_ecp_point_write_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int pk_write_ec_pubkey( unsigned char **p, unsigned char *start,
                                 mbedtls_ecp_keypair *ec )
{
    int ret;
    size_t len = 0;
    unsigned char buf[MBEDTLS_ECP_MAX_PT_LEN];

    if( ( ret = mbedtls_ecp_point_write_binary( &ec->grp, &ec->Q,
                                        MBEDTLS_ECP_PF_UNCOMPRESSED,
                                        &len, buf, sizeof( buf ) ) ) != 0 )
    {
        return( ret );
    }

    if( *p < start || (size_t)( *p - start ) < len )
        return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    *p -= len;
    memcpy( *p, buf, len );

    return( (int) len );
}