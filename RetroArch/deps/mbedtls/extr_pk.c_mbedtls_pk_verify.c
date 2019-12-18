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
struct TYPE_5__ {int /*<<< orphan*/  pk_ctx; TYPE_1__* pk_info; } ;
typedef  TYPE_2__ mbedtls_pk_context ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;
struct TYPE_4__ {int (* verify_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char const*,size_t) ;} ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_PK_TYPE_MISMATCH ; 
 scalar_t__ pk_hashlen_helper (int /*<<< orphan*/ ,size_t*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char const*,size_t) ; 

int mbedtls_pk_verify( mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg,
               const unsigned char *hash, size_t hash_len,
               const unsigned char *sig, size_t sig_len )
{
    if( ctx == NULL || ctx->pk_info == NULL ||
        pk_hashlen_helper( md_alg, &hash_len ) != 0 )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    if( ctx->pk_info->verify_func == NULL )
        return( MBEDTLS_ERR_PK_TYPE_MISMATCH );

    return( ctx->pk_info->verify_func( ctx->pk_ctx, md_alg, hash, hash_len,
                                       sig, sig_len ) );
}