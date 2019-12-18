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
struct hash_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; struct crypto_tfm* tfm; } ;
struct ahash_request {int /*<<< orphan*/  result; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_hash_cast (struct crypto_tfm*) ; 
 int digest (struct hash_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digest_async_digest(struct ahash_request *req)
{
	struct crypto_tfm *tfm  = req->base.tfm;
	struct hash_desc  desc = {
		.tfm   = __crypto_hash_cast(tfm),
		.flags = req->base.flags,
	};

	return digest(&desc, req->src, req->nbytes, req->result);
}