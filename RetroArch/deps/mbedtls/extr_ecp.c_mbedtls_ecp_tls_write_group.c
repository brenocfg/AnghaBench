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
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;
struct TYPE_6__ {int tls_id; } ;
typedef  TYPE_2__ mbedtls_ecp_curve_info ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ECP_TLS_NAMED_CURVE ; 
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL ; 
 TYPE_2__* mbedtls_ecp_curve_info_from_grp_id (int /*<<< orphan*/ ) ; 

int mbedtls_ecp_tls_write_group( const mbedtls_ecp_group *grp, size_t *olen,
                         unsigned char *buf, size_t blen )
{
    const mbedtls_ecp_curve_info *curve_info;

    if( ( curve_info = mbedtls_ecp_curve_info_from_grp_id( grp->id ) ) == NULL )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    /*
     * We are going to write 3 bytes (see below)
     */
    *olen = 3;
    if( blen < *olen )
        return( MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL );

    /*
     * First byte is curve_type, always named_curve
     */
    *buf++ = MBEDTLS_ECP_TLS_NAMED_CURVE;

    /*
     * Next two bytes are the namedcurve value
     */
    buf[0] = curve_info->tls_id >> 8;
    buf[1] = curve_info->tls_id & 0xFF;

    return( 0 );
}