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
typedef  int /*<<< orphan*/  mbedtls_sha512_context ;
typedef  int /*<<< orphan*/  mbedtls_sha256_context ;
struct TYPE_6__ {int initial_entropy_run; int source_count; unsigned char accumulator; int /*<<< orphan*/  mutex; TYPE_1__* source; } ;
typedef  TYPE_2__ mbedtls_entropy_context ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTROPY_MAX_LOOP ; 
 int MBEDTLS_ENTROPY_BLOCK_SIZE ; 
 int MBEDTLS_ERR_ENTROPY_SOURCE_FAILED ; 
 int MBEDTLS_ERR_THREADING_MUTEX_ERROR ; 
 int entropy_gather_internal (TYPE_2__*) ; 
 int mbedtls_entropy_update_nv_seed (TYPE_2__*) ; 
 int mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256 (unsigned char*,int,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha256_finish (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha256_starts (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha256_update (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_sha512 (unsigned char*,int,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha512_finish (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha512_starts (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha512_update (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int mbedtls_entropy_func( void *data, unsigned char *output, size_t len )
{
    int ret, count = 0, i, done;
    mbedtls_entropy_context *ctx = (mbedtls_entropy_context *) data;
    unsigned char buf[MBEDTLS_ENTROPY_BLOCK_SIZE];

    if( len > MBEDTLS_ENTROPY_BLOCK_SIZE )
        return( MBEDTLS_ERR_ENTROPY_SOURCE_FAILED );

#if defined(MBEDTLS_ENTROPY_NV_SEED)
    /* Update the NV entropy seed before generating any entropy for outside
     * use.
     */
    if( ctx->initial_entropy_run == 0 )
    {
        ctx->initial_entropy_run = 1;
        if( ( ret = mbedtls_entropy_update_nv_seed( ctx ) ) != 0 )
            return( ret );
    }
#endif

#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &ctx->mutex ) ) != 0 )
        return( ret );
#endif

    /*
     * Always gather extra entropy before a call
     */
    do
    {
        if( count++ > ENTROPY_MAX_LOOP )
        {
            ret = MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
            goto exit;
        }

        if( ( ret = entropy_gather_internal( ctx ) ) != 0 )
            goto exit;

        done = 1;
        for( i = 0; i < ctx->source_count; i++ )
            if( ctx->source[i].size < ctx->source[i].threshold )
                done = 0;
    }
    while( ! done );

    memset( buf, 0, MBEDTLS_ENTROPY_BLOCK_SIZE );

#if defined(MBEDTLS_ENTROPY_SHA512_ACCUMULATOR)
    mbedtls_sha512_finish( &ctx->accumulator, buf );

    /*
     * Reset accumulator and counters and recycle existing entropy
     */
    memset( &ctx->accumulator, 0, sizeof( mbedtls_sha512_context ) );
    mbedtls_sha512_starts( &ctx->accumulator, 0 );
    mbedtls_sha512_update( &ctx->accumulator, buf, MBEDTLS_ENTROPY_BLOCK_SIZE );

    /*
     * Perform second SHA-512 on entropy
     */
    mbedtls_sha512( buf, MBEDTLS_ENTROPY_BLOCK_SIZE, buf, 0 );
#else /* MBEDTLS_ENTROPY_SHA512_ACCUMULATOR */
    mbedtls_sha256_finish( &ctx->accumulator, buf );

    /*
     * Reset accumulator and counters and recycle existing entropy
     */
    memset( &ctx->accumulator, 0, sizeof( mbedtls_sha256_context ) );
    mbedtls_sha256_starts( &ctx->accumulator, 0 );
    mbedtls_sha256_update( &ctx->accumulator, buf, MBEDTLS_ENTROPY_BLOCK_SIZE );

    /*
     * Perform second SHA-256 on entropy
     */
    mbedtls_sha256( buf, MBEDTLS_ENTROPY_BLOCK_SIZE, buf, 0 );
#endif /* MBEDTLS_ENTROPY_SHA512_ACCUMULATOR */

    for( i = 0; i < ctx->source_count; i++ )
        ctx->source[i].size = 0;

    memcpy( output, buf, len );

    ret = 0;

exit:
#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &ctx->mutex ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    return( ret );
}