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
typedef  int /*<<< orphan*/  mbedtls_entropy_f_source_ptr ;
struct TYPE_5__ {int source_count; int /*<<< orphan*/  mutex; TYPE_1__* source; } ;
typedef  TYPE_2__ mbedtls_entropy_context ;
struct TYPE_4__ {size_t threshold; int strong; void* p_source; int /*<<< orphan*/  f_source; } ;

/* Variables and functions */
 int MBEDTLS_ENTROPY_MAX_SOURCES ; 
 int MBEDTLS_ERR_ENTROPY_MAX_SOURCES ; 
 int MBEDTLS_ERR_THREADING_MUTEX_ERROR ; 
 int mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 

int mbedtls_entropy_add_source( mbedtls_entropy_context *ctx,
                        mbedtls_entropy_f_source_ptr f_source, void *p_source,
                        size_t threshold, int strong )
{
    int index, ret = 0;

#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &ctx->mutex ) ) != 0 )
        return( ret );
#endif

    index = ctx->source_count;
    if( index >= MBEDTLS_ENTROPY_MAX_SOURCES )
    {
        ret = MBEDTLS_ERR_ENTROPY_MAX_SOURCES;
        goto exit;
    }

    ctx->source[index].f_source  = f_source;
    ctx->source[index].p_source  = p_source;
    ctx->source[index].threshold = threshold;
    ctx->source[index].strong    = strong;

    ctx->source_count++;

exit:
#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &ctx->mutex ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    return( ret );
}