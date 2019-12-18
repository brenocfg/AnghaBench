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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {unsigned char* name; int /*<<< orphan*/  ctx; scalar_t__ generation_time; } ;
typedef  TYPE_1__ mbedtls_ssl_ticket_key ;
struct TYPE_5__ {int (* f_rng ) (int /*<<< orphan*/ ,unsigned char*,int) ;int /*<<< orphan*/  p_rng; TYPE_1__* keys; } ;
typedef  TYPE_2__ mbedtls_ssl_ticket_context ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAX_KEY_BYTES ; 
 int /*<<< orphan*/  MBEDTLS_ENCRYPT ; 
 int /*<<< orphan*/  mbedtls_cipher_get_key_bitlen (int /*<<< orphan*/ *) ; 
 int mbedtls_cipher_setkey (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int ssl_ticket_gen_key( mbedtls_ssl_ticket_context *ctx,
                               unsigned char index )
{
    int ret;
    unsigned char buf[MAX_KEY_BYTES];
    mbedtls_ssl_ticket_key *key = ctx->keys + index;

#if defined(MBEDTLS_HAVE_TIME)
    key->generation_time = (uint32_t) mbedtls_time( NULL );
#endif

    if( ( ret = ctx->f_rng( ctx->p_rng, key->name, sizeof( key->name ) ) ) != 0 )
        return( ret );

    if( ( ret = ctx->f_rng( ctx->p_rng, buf, sizeof( buf ) ) ) != 0 )
        return( ret );

    /* With GCM and CCM, same context can encrypt & decrypt */
    ret = mbedtls_cipher_setkey( &key->ctx, buf,
                                 mbedtls_cipher_get_key_bitlen( &key->ctx ),
                                 MBEDTLS_ENCRYPT );

    mbedtls_zeroize( buf, sizeof( buf ) );

    return( ret );
}