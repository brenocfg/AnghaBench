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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct chksum_desc_ctx {int /*<<< orphan*/  crc; } ;
struct chksum_ctx {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 struct chksum_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 struct chksum_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int chksum_init(struct shash_desc *desc)
{
	struct chksum_ctx *mctx = crypto_shash_ctx(desc->tfm);
	struct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->crc = mctx->key;

	return 0;
}