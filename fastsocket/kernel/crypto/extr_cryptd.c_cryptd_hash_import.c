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
struct cryptd_hash_request_ctx {int /*<<< orphan*/  desc; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct cryptd_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int crypto_shash_import (int /*<<< orphan*/ *,void const*) ; 

__attribute__((used)) static int cryptd_hash_import(struct ahash_request *req, const void *in)
{
	struct cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);

	return crypto_shash_import(&rctx->desc, in);
}