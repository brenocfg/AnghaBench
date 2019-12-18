#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int nr; int /*<<< orphan*/ * rk; } ;
typedef  TYPE_1__ mbedtls_camellia_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_camellia_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_camellia_init (TYPE_1__*) ; 
 int mbedtls_camellia_setkey_enc (TYPE_1__*,unsigned char const*,unsigned int) ; 

int mbedtls_camellia_setkey_dec( mbedtls_camellia_context *ctx, const unsigned char *key,
                         unsigned int keybits )
{
    int idx, ret;
    size_t i;
    mbedtls_camellia_context cty;
    uint32_t *RK;
    uint32_t *SK;

    mbedtls_camellia_init( &cty );

    /* Also checks keybits */
    if( ( ret = mbedtls_camellia_setkey_enc( &cty, key, keybits ) ) != 0 )
        goto exit;

    ctx->nr = cty.nr;
    idx = ( ctx->nr == 4 );

    RK = ctx->rk;
    SK = cty.rk + 24 * 2 + 8 * idx * 2;

    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;

    for( i = 22 + 8 * idx, SK -= 6; i > 0; i--, SK -= 4 )
    {
        *RK++ = *SK++;
        *RK++ = *SK++;
    }

    SK -= 2;

    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;

exit:
    mbedtls_camellia_free( &cty );

    return( ret );
}