#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ header_size; } ;
struct iso_context {int header_length; TYPE_1__ base; scalar_t__ header; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __swab32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 

__attribute__((used)) static void copy_iso_headers(struct iso_context *ctx, void *p)
{
	int i = ctx->header_length;

	if (i + ctx->base.header_size > PAGE_SIZE)
		return;

	/*
	 * The iso header is byteswapped to little endian by
	 * the controller, but the remaining header quadlets
	 * are big endian.  We want to present all the headers
	 * as big endian, so we have to swap the first quadlet.
	 */
	if (ctx->base.header_size > 0)
		*(u32 *) (ctx->header + i) = __swab32(*(u32 *) (p + 4));
	if (ctx->base.header_size > 4)
		*(u32 *) (ctx->header + i + 4) = __swab32(*(u32 *) p);
	if (ctx->base.header_size > 8)
		memcpy(ctx->header + i + 8, p + 8, ctx->base.header_size - 8);
	ctx->header_length += ctx->base.header_size;
}