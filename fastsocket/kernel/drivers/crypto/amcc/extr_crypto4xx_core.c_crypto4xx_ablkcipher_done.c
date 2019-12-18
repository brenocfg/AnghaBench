#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct pd_uinfo {struct scatterlist* dest_va; scalar_t__ using_sd; int /*<<< orphan*/  async_req; } ;
struct crypto4xx_device {TYPE_1__* core_dev; } ;
struct crypto4xx_ctx {int dummy; } ;
struct ce_pd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* complete ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {TYPE_2__ base; int /*<<< orphan*/  dst; int /*<<< orphan*/  nbytes; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto4xx_copy_pkt_to_dst (struct crypto4xx_device*,struct ce_pd*,struct pd_uinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto4xx_ret_sg_desc (struct crypto4xx_device*,struct pd_uinfo*) ; 
 struct crypto4xx_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 crypto4xx_ablkcipher_done(struct crypto4xx_device *dev,
				     struct pd_uinfo *pd_uinfo,
				     struct ce_pd *pd)
{
	struct crypto4xx_ctx *ctx;
	struct ablkcipher_request *ablk_req;
	struct scatterlist *dst;
	dma_addr_t addr;

	ablk_req = ablkcipher_request_cast(pd_uinfo->async_req);
	ctx  = crypto_tfm_ctx(ablk_req->base.tfm);

	if (pd_uinfo->using_sd) {
		crypto4xx_copy_pkt_to_dst(dev, pd, pd_uinfo, ablk_req->nbytes,
					  ablk_req->dst);
	} else {
		dst = pd_uinfo->dest_va;
		addr = dma_map_page(dev->core_dev->device, sg_page(dst),
				    dst->offset, dst->length, DMA_FROM_DEVICE);
	}
	crypto4xx_ret_sg_desc(dev, pd_uinfo);
	if (ablk_req->base.complete != NULL)
		ablk_req->base.complete(&ablk_req->base, 0);

	return 0;
}