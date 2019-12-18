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
typedef  int /*<<< orphan*/  u8 ;
struct ghash_desc_ctx {scalar_t__ bytes; int /*<<< orphan*/ * buffer; } ;
struct ghash_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GHASH_BLOCK_SIZE ; 
 int /*<<< orphan*/  KIMD_GHASH ; 
 int crypt_s390_kimd (int /*<<< orphan*/ ,struct ghash_ctx*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ghash_flush(struct ghash_ctx *ctx, struct ghash_desc_ctx *dctx)
{
	u8 *buf = dctx->buffer;
	int ret;

	if (dctx->bytes) {
		u8 *pos = buf + (GHASH_BLOCK_SIZE - dctx->bytes);

		memset(pos, 0, dctx->bytes);

		ret = crypt_s390_kimd(KIMD_GHASH, ctx, buf, GHASH_BLOCK_SIZE);
		BUG_ON(ret != GHASH_BLOCK_SIZE);
	}

	dctx->bytes = 0;
}