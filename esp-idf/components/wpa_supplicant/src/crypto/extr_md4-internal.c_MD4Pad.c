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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD4Update (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int MD4_BLOCK_LENGTH ; 
 int /*<<< orphan*/ * PADDING ; 
 int /*<<< orphan*/  PUT_64BIT_LE (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void MD4Pad(MD4_CTX *ctx)
{
	u8 count[8];
	size_t padlen;

	PUT_64BIT_LE(count, ctx->count);

	padlen = MD4_BLOCK_LENGTH -
		((ctx->count >> 3) & (MD4_BLOCK_LENGTH - 1));
	if (padlen < 1 + 8)
		padlen += MD4_BLOCK_LENGTH;
	MD4Update(ctx, PADDING, padlen - 8);
	MD4Update(ctx, count, 8);
}