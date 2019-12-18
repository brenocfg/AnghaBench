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
struct zlib_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct zlib_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  zlib_comp_exit (struct zlib_ctx*) ; 
 int /*<<< orphan*/  zlib_decomp_exit (struct zlib_ctx*) ; 

__attribute__((used)) static void zlib_exit(struct crypto_tfm *tfm)
{
	struct zlib_ctx *ctx = crypto_tfm_ctx(tfm);

	zlib_comp_exit(ctx);
	zlib_decomp_exit(ctx);
}