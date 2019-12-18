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
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ mbedtls_ssl_ticket_key ;
struct TYPE_6__ {TYPE_1__* keys; } ;
typedef  TYPE_2__ mbedtls_ssl_ticket_context ;

/* Variables and functions */
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static mbedtls_ssl_ticket_key *ssl_ticket_select_key(
        mbedtls_ssl_ticket_context *ctx,
        const unsigned char name[4] )
{
    unsigned char i;

    for( i = 0; i < sizeof( ctx->keys ) / sizeof( *ctx->keys ); i++ )
        if( memcmp( name, ctx->keys[i].name, 4 ) == 0 )
            return( &ctx->keys[i] );

    return( NULL );
}