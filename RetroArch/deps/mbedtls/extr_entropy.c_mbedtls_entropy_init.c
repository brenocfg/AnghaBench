#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  havege_data; int /*<<< orphan*/  accumulator; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ mbedtls_entropy_context ;

/* Variables and functions */
 int MBEDTLS_ENTROPY_BLOCK_SIZE ; 
 int MBEDTLS_ENTROPY_MIN_HARDCLOCK ; 
 int MBEDTLS_ENTROPY_MIN_HARDWARE ; 
 int MBEDTLS_ENTROPY_MIN_HAVEGE ; 
 int MBEDTLS_ENTROPY_MIN_PLATFORM ; 
 int /*<<< orphan*/  MBEDTLS_ENTROPY_SOURCE_STRONG ; 
 int /*<<< orphan*/  MBEDTLS_ENTROPY_SOURCE_WEAK ; 
 int /*<<< orphan*/  mbedtls_entropy_add_source (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_hardclock_poll ; 
 int /*<<< orphan*/  mbedtls_hardware_poll ; 
 int /*<<< orphan*/  mbedtls_havege_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_havege_poll ; 
 int /*<<< orphan*/  mbedtls_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_null_entropy_poll ; 
 int /*<<< orphan*/  mbedtls_nv_seed_poll ; 
 int /*<<< orphan*/  mbedtls_platform_entropy_poll ; 
 int /*<<< orphan*/  mbedtls_sha256_starts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha512_starts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void mbedtls_entropy_init( mbedtls_entropy_context *ctx )
{
    memset( ctx, 0, sizeof(mbedtls_entropy_context) );

#if defined(MBEDTLS_THREADING_C)
    mbedtls_mutex_init( &ctx->mutex );
#endif

#if defined(MBEDTLS_ENTROPY_SHA512_ACCUMULATOR)
    mbedtls_sha512_starts( &ctx->accumulator, 0 );
#else
    mbedtls_sha256_starts( &ctx->accumulator, 0 );
#endif
#if defined(MBEDTLS_HAVEGE_C)
    mbedtls_havege_init( &ctx->havege_data );
#endif

#if defined(MBEDTLS_TEST_NULL_ENTROPY)
    mbedtls_entropy_add_source( ctx, mbedtls_null_entropy_poll, NULL,
                                1, MBEDTLS_ENTROPY_SOURCE_STRONG );
#endif

#if !defined(MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES)
#if !defined(MBEDTLS_NO_PLATFORM_ENTROPY)
    mbedtls_entropy_add_source( ctx, mbedtls_platform_entropy_poll, NULL,
                                MBEDTLS_ENTROPY_MIN_PLATFORM,
                                MBEDTLS_ENTROPY_SOURCE_STRONG );
#endif
#if defined(MBEDTLS_TIMING_C)
    mbedtls_entropy_add_source( ctx, mbedtls_hardclock_poll, NULL,
                                MBEDTLS_ENTROPY_MIN_HARDCLOCK,
                                MBEDTLS_ENTROPY_SOURCE_WEAK );
#endif
#if defined(MBEDTLS_HAVEGE_C)
    mbedtls_entropy_add_source( ctx, mbedtls_havege_poll, &ctx->havege_data,
                                MBEDTLS_ENTROPY_MIN_HAVEGE,
                                MBEDTLS_ENTROPY_SOURCE_STRONG );
#endif
#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT)
    mbedtls_entropy_add_source( ctx, mbedtls_hardware_poll, NULL,
                                MBEDTLS_ENTROPY_MIN_HARDWARE,
                                MBEDTLS_ENTROPY_SOURCE_STRONG );
#endif
#if defined(MBEDTLS_ENTROPY_NV_SEED)
    mbedtls_entropy_add_source( ctx, mbedtls_nv_seed_poll, NULL,
                                MBEDTLS_ENTROPY_BLOCK_SIZE,
                                MBEDTLS_ENTROPY_SOURCE_STRONG );
#endif
#endif /* MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES */
}