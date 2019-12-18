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
typedef  int /*<<< orphan*/  mbedtls_ecp_group_id ;
struct TYPE_3__ {int /*<<< orphan*/  Q; int /*<<< orphan*/  d; int /*<<< orphan*/  grp; } ;
typedef  TYPE_1__ mbedtls_ecdsa_context ;

/* Variables and functions */
 scalar_t__ mbedtls_ecp_gen_keypair (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int (*) (void*,unsigned char*,size_t),void*) ; 
 scalar_t__ mbedtls_ecp_group_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mbedtls_ecdsa_genkey( mbedtls_ecdsa_context *ctx, mbedtls_ecp_group_id gid,
                  int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    return( mbedtls_ecp_group_load( &ctx->grp, gid ) ||
            mbedtls_ecp_gen_keypair( &ctx->grp, &ctx->d, &ctx->Q, f_rng, p_rng ) );
}