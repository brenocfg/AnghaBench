#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_7__ {TYPE_2__ dn_hash; TYPE_1__* dn_hash_impl; } ;
typedef  TYPE_3__ br_x509_minimal_context ;
struct TYPE_5__ {int /*<<< orphan*/  (* out ) (int /*<<< orphan*/ *,unsigned char*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,void const*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static void
hash_dn(br_x509_minimal_context *ctx, const void *dn, size_t len,
	unsigned char *out)
{
	ctx->dn_hash_impl->init(&ctx->dn_hash.vtable);
	ctx->dn_hash_impl->update(&ctx->dn_hash.vtable, dn, len);
	ctx->dn_hash_impl->out(&ctx->dn_hash.vtable, out);
}