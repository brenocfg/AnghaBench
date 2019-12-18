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
struct shash_desc {int dummy; } ;
struct md5_ctx {int* hash; scalar_t__ byte_count; } ;

/* Variables and functions */
 struct md5_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int md5_init(struct shash_desc *desc)
{
	struct md5_ctx *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = 0x67452301;
	mctx->hash[1] = 0xefcdab89;
	mctx->hash[2] = 0x98badcfe;
	mctx->hash[3] = 0x10325476;
	mctx->byte_count = 0;

	return 0;
}