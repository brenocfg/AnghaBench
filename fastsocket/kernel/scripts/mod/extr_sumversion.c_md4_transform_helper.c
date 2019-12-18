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
typedef  int /*<<< orphan*/  uint32_t ;
struct md4_ctx {int /*<<< orphan*/  block; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  md4_transform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void md4_transform_helper(struct md4_ctx *ctx)
{
	le32_to_cpu_array(ctx->block, sizeof(ctx->block) / sizeof(uint32_t));
	md4_transform(ctx->hash, ctx->block);
}