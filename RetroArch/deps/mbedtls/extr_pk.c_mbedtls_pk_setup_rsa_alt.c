#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  key_len_func; int /*<<< orphan*/  sign_func; int /*<<< orphan*/  decrypt_func; void* key; } ;
typedef  TYPE_1__ mbedtls_rsa_alt_context ;
typedef  int /*<<< orphan*/  mbedtls_pk_rsa_alt_sign_func ;
typedef  int /*<<< orphan*/  mbedtls_pk_rsa_alt_key_len_func ;
typedef  int /*<<< orphan*/  mbedtls_pk_rsa_alt_decrypt_func ;
struct TYPE_7__ {int /*<<< orphan*/ * (* ctx_alloc_func ) () ;} ;
typedef  TYPE_2__ mbedtls_pk_info_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pk_ctx; TYPE_2__ const* pk_info; } ;
typedef  TYPE_3__ mbedtls_pk_context ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_ALLOC_FAILED ; 
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 TYPE_2__ mbedtls_rsa_alt_info ; 
 int /*<<< orphan*/ * stub1 () ; 

int mbedtls_pk_setup_rsa_alt( mbedtls_pk_context *ctx, void * key,
                         mbedtls_pk_rsa_alt_decrypt_func decrypt_func,
                         mbedtls_pk_rsa_alt_sign_func sign_func,
                         mbedtls_pk_rsa_alt_key_len_func key_len_func )
{
    mbedtls_rsa_alt_context *rsa_alt;
    const mbedtls_pk_info_t *info = &mbedtls_rsa_alt_info;

    if( ctx == NULL || ctx->pk_info != NULL )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    if( ( ctx->pk_ctx = info->ctx_alloc_func() ) == NULL )
        return( MBEDTLS_ERR_PK_ALLOC_FAILED );

    ctx->pk_info = info;

    rsa_alt = (mbedtls_rsa_alt_context *) ctx->pk_ctx;

    rsa_alt->key = key;
    rsa_alt->decrypt_func = decrypt_func;
    rsa_alt->sign_func = sign_func;
    rsa_alt->key_len_func = key_len_func;

    return( 0 );
}