#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int (* f_rng ) (void*,unsigned char*,size_t) ;TYPE_1__* keys; int /*<<< orphan*/  ticket_lifetime; void* p_rng; } ;
typedef  TYPE_2__ mbedtls_ssl_ticket_context ;
typedef  int /*<<< orphan*/  mbedtls_cipher_type_t ;
struct TYPE_10__ {scalar_t__ mode; int key_bitlen; } ;
typedef  TYPE_3__ mbedtls_cipher_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int MAX_KEY_BYTES ; 
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 scalar_t__ MBEDTLS_MODE_CCM ; 
 scalar_t__ MBEDTLS_MODE_GCM ; 
 TYPE_3__* mbedtls_cipher_info_from_type (int /*<<< orphan*/ ) ; 
 int mbedtls_cipher_setup (int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int ssl_ticket_gen_key (TYPE_2__*,int) ; 

int mbedtls_ssl_ticket_setup( mbedtls_ssl_ticket_context *ctx,
    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
    mbedtls_cipher_type_t cipher,
    uint32_t lifetime )
{
    int ret;
    const mbedtls_cipher_info_t *cipher_info;

    ctx->f_rng = f_rng;
    ctx->p_rng = p_rng;

    ctx->ticket_lifetime = lifetime;

    cipher_info = mbedtls_cipher_info_from_type( cipher);
    if( cipher_info == NULL )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    if( cipher_info->mode != MBEDTLS_MODE_GCM &&
        cipher_info->mode != MBEDTLS_MODE_CCM )
    {
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
    }

    if( cipher_info->key_bitlen > 8 * MAX_KEY_BYTES )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    if( ( ret = mbedtls_cipher_setup( &ctx->keys[0].ctx, cipher_info ) ) != 0 ||
        ( ret = mbedtls_cipher_setup( &ctx->keys[1].ctx, cipher_info ) ) != 0 )
    {
        return( ret );
    }

    if( ( ret = ssl_ticket_gen_key( ctx, 0 ) ) != 0 ||
        ( ret = ssl_ticket_gen_key( ctx, 1 ) ) != 0 )
    {
        return( ret );
    }

    return( 0 );
}