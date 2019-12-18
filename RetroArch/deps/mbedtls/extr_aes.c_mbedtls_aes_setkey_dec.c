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
typedef  int uint32_t ;
struct TYPE_6__ {int* rk; int* buf; int nr; } ;
typedef  TYPE_1__ mbedtls_aes_context ;

/* Variables and functions */
 size_t* FSb ; 
 int /*<<< orphan*/  MBEDTLS_AESNI_AES ; 
 int /*<<< orphan*/  MBEDTLS_PADLOCK_ACE ; 
 int* MBEDTLS_PADLOCK_ALIGN16 (int*) ; 
 int* RT0 ; 
 int* RT1 ; 
 int* RT2 ; 
 int* RT3 ; 
 int aes_padlock_ace ; 
 int /*<<< orphan*/  mbedtls_aes_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_aes_init (TYPE_1__*) ; 
 int mbedtls_aes_setkey_enc (TYPE_1__*,unsigned char const*,unsigned int) ; 
 scalar_t__ mbedtls_aesni_has_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_aesni_inverse_key (unsigned char*,unsigned char const*,int) ; 
 int mbedtls_padlock_has_support (int /*<<< orphan*/ ) ; 

int mbedtls_aes_setkey_dec( mbedtls_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits )
{
    int i, j, ret;
    mbedtls_aes_context cty;
    uint32_t *RK;
    uint32_t *SK;

    mbedtls_aes_init( &cty );

#if defined(MBEDTLS_PADLOCK_C) && defined(MBEDTLS_PADLOCK_ALIGN16)
    if( aes_padlock_ace == -1 )
        aes_padlock_ace = mbedtls_padlock_has_support( MBEDTLS_PADLOCK_ACE );

    if( aes_padlock_ace )
        ctx->rk = RK = MBEDTLS_PADLOCK_ALIGN16( ctx->buf );
    else
#endif
    ctx->rk = RK = ctx->buf;

    /* Also checks keybits */
    if( ( ret = mbedtls_aes_setkey_enc( &cty, key, keybits ) ) != 0 )
        goto exit;

    ctx->nr = cty.nr;

#if defined(MBEDTLS_AESNI_C) && defined(MBEDTLS_HAVE_X86_64)
    if( mbedtls_aesni_has_support( MBEDTLS_AESNI_AES ) )
    {
        mbedtls_aesni_inverse_key( (unsigned char *) ctx->rk,
                           (const unsigned char *) cty.rk, ctx->nr );
        goto exit;
    }
#endif

    SK = cty.rk + cty.nr * 4;

    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;

    for( i = ctx->nr - 1, SK -= 8; i > 0; i--, SK -= 8 )
    {
        for( j = 0; j < 4; j++, SK++ )
        {
            *RK++ = RT0[ FSb[ ( *SK       ) & 0xFF ] ] ^
                    RT1[ FSb[ ( *SK >>  8 ) & 0xFF ] ] ^
                    RT2[ FSb[ ( *SK >> 16 ) & 0xFF ] ] ^
                    RT3[ FSb[ ( *SK >> 24 ) & 0xFF ] ];
        }
    }

    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;

exit:
    mbedtls_aes_free( &cty );

    return( ret );
}