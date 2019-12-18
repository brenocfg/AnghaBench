#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {TYPE_2__* session_negotiate; TYPE_1__* session; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_6__ {int verify_result; } ;
struct TYPE_5__ {int verify_result; } ;

/* Variables and functions */

uint32_t mbedtls_ssl_get_verify_result( const mbedtls_ssl_context *ssl )
{
    if( ssl->session != NULL )
        return( ssl->session->verify_result );

    if( ssl->session_negotiate != NULL )
        return( ssl->session_negotiate->verify_result );

    return( 0xFFFFFFFF );
}