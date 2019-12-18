#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_1__ mbedtls_ssl_cache_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES ; 
 int /*<<< orphan*/  MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  mbedtls_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void mbedtls_ssl_cache_init( mbedtls_ssl_cache_context *cache )
{
    memset( cache, 0, sizeof( mbedtls_ssl_cache_context ) );

    cache->timeout = MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT;
    cache->max_entries = MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES;

#if defined(MBEDTLS_THREADING_C)
    mbedtls_mutex_init( &cache->mutex );
#endif
}