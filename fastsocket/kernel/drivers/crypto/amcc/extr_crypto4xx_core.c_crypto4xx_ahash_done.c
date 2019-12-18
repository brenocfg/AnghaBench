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
typedef  int /*<<< orphan*/  u32 ;
struct pd_uinfo {int /*<<< orphan*/  async_req; } ;
struct crypto4xx_device {int dummy; } ;
struct crypto4xx_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tfm; } ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto4xx_copy_digest_to_dst (struct pd_uinfo*,struct crypto4xx_ctx*) ; 
 int /*<<< orphan*/  crypto4xx_ret_sg_desc (struct crypto4xx_device*,struct pd_uinfo*) ; 
 struct crypto4xx_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 crypto4xx_ahash_done(struct crypto4xx_device *dev,
				struct pd_uinfo *pd_uinfo)
{
	struct crypto4xx_ctx *ctx;
	struct ahash_request *ahash_req;

	ahash_req = ahash_request_cast(pd_uinfo->async_req);
	ctx  = crypto_tfm_ctx(ahash_req->base.tfm);

	crypto4xx_copy_digest_to_dst(pd_uinfo,
				     crypto_tfm_ctx(ahash_req->base.tfm));
	crypto4xx_ret_sg_desc(dev, pd_uinfo);
	/* call user provided callback function x */
	if (ahash_req->base.complete != NULL)
		ahash_req->base.complete(&ahash_req->base, 0);

	return 0;
}