#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_2__** policy_vtable; } ;
typedef  TYPE_1__ br_ssl_server_context ;
struct TYPE_6__ {int /*<<< orphan*/  (* do_keyx ) (TYPE_2__**,unsigned char*,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ecdh_common (TYPE_1__*,int,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,unsigned char*,size_t*) ; 

__attribute__((used)) static void
do_ecdh(br_ssl_server_context *ctx, int prf_id,
	unsigned char *cpoint, size_t cpoint_len)
{
	uint32_t x;

	/*
	 * Finalise the key exchange.
	 */
	x = (*ctx->policy_vtable)->do_keyx(ctx->policy_vtable,
		cpoint, &cpoint_len);
	ecdh_common(ctx, prf_id, cpoint, cpoint_len, x);
}