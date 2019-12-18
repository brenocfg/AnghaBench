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
struct TYPE_6__ {int source_count; TYPE_1__* source; } ;
typedef  TYPE_2__ mbedtls_entropy_context ;
struct TYPE_5__ {scalar_t__ strong; int (* f_source ) (int /*<<< orphan*/ ,unsigned char*,int,size_t*) ;size_t size; int /*<<< orphan*/  p_source; } ;

/* Variables and functions */
 int MBEDTLS_ENTROPY_MAX_GATHER ; 
 scalar_t__ MBEDTLS_ENTROPY_SOURCE_STRONG ; 
 int MBEDTLS_ERR_ENTROPY_NO_SOURCES_DEFINED ; 
 int MBEDTLS_ERR_ENTROPY_NO_STRONG_SOURCE ; 
 int /*<<< orphan*/  entropy_update (TYPE_2__*,unsigned char,unsigned char*,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int,size_t*) ; 

__attribute__((used)) static int entropy_gather_internal( mbedtls_entropy_context *ctx )
{
    int ret, i, have_one_strong = 0;
    unsigned char buf[MBEDTLS_ENTROPY_MAX_GATHER];
    size_t olen;

    if( ctx->source_count == 0 )
        return( MBEDTLS_ERR_ENTROPY_NO_SOURCES_DEFINED );

    /*
     * Run through our entropy sources
     */
    for( i = 0; i < ctx->source_count; i++ )
    {
        if( ctx->source[i].strong == MBEDTLS_ENTROPY_SOURCE_STRONG )
            have_one_strong = 1;

        olen = 0;
        if( ( ret = ctx->source[i].f_source( ctx->source[i].p_source,
                        buf, MBEDTLS_ENTROPY_MAX_GATHER, &olen ) ) != 0 )
        {
            return( ret );
        }

        /*
         * Add if we actually gathered something
         */
        if( olen > 0 )
        {
            entropy_update( ctx, (unsigned char) i, buf, olen );
            ctx->source[i].size += olen;
        }
    }

    if( have_one_strong == 0 )
        return( MBEDTLS_ERR_ENTROPY_NO_STRONG_SOURCE );

    return( 0 );
}