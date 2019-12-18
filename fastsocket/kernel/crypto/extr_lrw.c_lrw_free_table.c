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
struct lrw_table_ctx {scalar_t__ table; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf128mul_free_64k (scalar_t__) ; 

void lrw_free_table(struct lrw_table_ctx *ctx)
{
	if (ctx->table)
		gf128mul_free_64k(ctx->table);
}