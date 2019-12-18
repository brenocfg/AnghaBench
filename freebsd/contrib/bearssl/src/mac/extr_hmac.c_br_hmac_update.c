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
struct TYPE_5__ {TYPE_3__* vtable; } ;
struct TYPE_6__ {TYPE_1__ dig; } ;
typedef  TYPE_2__ br_hmac_context ;
struct TYPE_7__ {int /*<<< orphan*/  (* update ) (TYPE_3__**,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__**,void const*,size_t) ; 

void
br_hmac_update(br_hmac_context *ctx, const void *data, size_t len)
{
	ctx->dig.vtable->update(&ctx->dig.vtable, data, len);
}