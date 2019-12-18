#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
union dynamic_sa_contents {int /*<<< orphan*/  w; } ;
typedef  int u32 ;
struct dynamic_sa_ctl {int /*<<< orphan*/  sa_contents; } ;
struct crypto4xx_ctx {scalar_t__ direction; scalar_t__ sa_out; scalar_t__ sa_in; } ;

/* Variables and functions */
 scalar_t__ DIR_INBOUND ; 

u32 get_dynamic_sa_offset_key_field(struct crypto4xx_ctx *ctx)
{
	union dynamic_sa_contents cts;

	if (ctx->direction == DIR_INBOUND)
		cts.w = ((struct dynamic_sa_ctl *) ctx->sa_in)->sa_contents;
	else
		cts.w = ((struct dynamic_sa_ctl *) ctx->sa_out)->sa_contents;

	return sizeof(struct dynamic_sa_ctl);
}