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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ ticket_lifetime; size_t active; TYPE_1__* keys; } ;
typedef  TYPE_2__ mbedtls_ssl_ticket_context ;
struct TYPE_5__ {scalar_t__ generation_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_time (int /*<<< orphan*/ *) ; 
 int ssl_ticket_gen_key (TYPE_2__*,int) ; 

__attribute__((used)) static int ssl_ticket_update_keys( mbedtls_ssl_ticket_context *ctx )
{
#if !defined(MBEDTLS_HAVE_TIME)
    ((void) ctx);
#else
    if( ctx->ticket_lifetime != 0 )
    {
        uint32_t current_time = (uint32_t) mbedtls_time( NULL );
        uint32_t key_time = ctx->keys[ctx->active].generation_time;

        if( current_time > key_time &&
            current_time - key_time < ctx->ticket_lifetime )
        {
            return( 0 );
        }

        ctx->active = 1 - ctx->active;

        return( ssl_ticket_gen_key( ctx, ctx->active ) );
    }
    else
#endif /* MBEDTLS_HAVE_TIME */
        return( 0 );
}