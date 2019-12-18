#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct lrw_table_ctx {int /*<<< orphan*/  table; TYPE_1__* mulinc; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ be128 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  gf128mul_64k_bbe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf128mul_free_64k (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf128mul_init_64k_bbe (TYPE_1__*) ; 
 int /*<<< orphan*/  setbit128_bbe (TYPE_1__*,int) ; 

int lrw_init_table(struct lrw_table_ctx *ctx, const u8 *tweak)
{
	be128 tmp = { 0 };
	int i;

	if (ctx->table)
		gf128mul_free_64k(ctx->table);

	/* initialize multiplication table for Key2 */
	ctx->table = gf128mul_init_64k_bbe((be128 *)tweak);
	if (!ctx->table)
		return -ENOMEM;

	/* initialize optimization table */
	for (i = 0; i < 128; i++) {
		setbit128_bbe(&tmp, i);
		ctx->mulinc[i] = tmp;
		gf128mul_64k_bbe(&ctx->mulinc[i], ctx->table);
	}

	return 0;
}