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
struct TYPE_5__ {int minor_ver; TYPE_1__* conf; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_4__ {scalar_t__ transport; } ;

/* Variables and functions */
#define  MBEDTLS_SSL_MINOR_VERSION_0 131 
#define  MBEDTLS_SSL_MINOR_VERSION_1 130 
#define  MBEDTLS_SSL_MINOR_VERSION_2 129 
#define  MBEDTLS_SSL_MINOR_VERSION_3 128 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 

const char *mbedtls_ssl_get_version( const mbedtls_ssl_context *ssl )
{
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        switch( ssl->minor_ver )
        {
            case MBEDTLS_SSL_MINOR_VERSION_2:
                return( "DTLSv1.0" );

            case MBEDTLS_SSL_MINOR_VERSION_3:
                return( "DTLSv1.2" );

            default:
                return( "unknown (DTLS)" );
        }
    }
#endif

    switch( ssl->minor_ver )
    {
        case MBEDTLS_SSL_MINOR_VERSION_0:
            return( "SSLv3.0" );

        case MBEDTLS_SSL_MINOR_VERSION_1:
            return( "TLSv1.0" );

        case MBEDTLS_SSL_MINOR_VERSION_2:
            return( "TLSv1.1" );

        case MBEDTLS_SSL_MINOR_VERSION_3:
            return( "TLSv1.2" );

        default:
            return( "unknown" );
    }
}