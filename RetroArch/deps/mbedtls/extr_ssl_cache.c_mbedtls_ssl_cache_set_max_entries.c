#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_entries; } ;
typedef  TYPE_1__ mbedtls_ssl_cache_context ;

/* Variables and functions */

void mbedtls_ssl_cache_set_max_entries( mbedtls_ssl_cache_context *cache, int max )
{
    if( max < 0 ) max = 0;

    cache->max_entries = max;
}