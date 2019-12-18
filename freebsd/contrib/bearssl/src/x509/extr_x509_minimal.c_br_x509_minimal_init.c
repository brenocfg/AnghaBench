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
typedef  int /*<<< orphan*/  br_x509_trust_anchor ;
struct TYPE_4__ {size_t trust_anchors_num; int /*<<< orphan*/  const* trust_anchors; int /*<<< orphan*/  const* dn_hash_impl; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ br_x509_minimal_context ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_x509_minimal_vtable ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
br_x509_minimal_init(br_x509_minimal_context *ctx,
	const br_hash_class *dn_hash_impl,
	const br_x509_trust_anchor *trust_anchors, size_t trust_anchors_num)
{
	memset(ctx, 0, sizeof *ctx);
	ctx->vtable = &br_x509_minimal_vtable;
	ctx->dn_hash_impl = dn_hash_impl;
	ctx->trust_anchors = trust_anchors;
	ctx->trust_anchors_num = trust_anchors_num;
}