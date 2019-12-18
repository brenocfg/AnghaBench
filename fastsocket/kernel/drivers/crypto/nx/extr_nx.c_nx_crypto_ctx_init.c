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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct nx_sg {int dummy; } ;
struct nx_csbcpb {int dummy; } ;
struct nx_crypto_ctx {int kmem_len; int /*<<< orphan*/  props; int /*<<< orphan*/ * stats; struct nx_sg* out_sg; struct nx_csbcpb* csbcpb_aead; struct nx_sg* in_sg; struct nx_csbcpb* csbcpb; scalar_t__ kmem; } ;
struct alg_props {int dummy; } ;
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/ ** ap; } ;
struct TYPE_4__ {TYPE_1__ of; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NX_MODE_AES_CCM ; 
 size_t NX_MODE_AES_GCM ; 
 scalar_t__ NX_OKAY ; 
 int NX_PAGE_SIZE ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ nx_driver ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nx_crypto_ctx_init(struct nx_crypto_ctx *nx_ctx, u32 fc, u32 mode)
{
	if (nx_driver.of.status != NX_OKAY) {
		pr_err("Attempt to initialize NX crypto context while device "
		       "is not available!\n");
		return -ENODEV;
	}

	/* we need an extra page for csbcpb_aead for these modes */
	if (mode == NX_MODE_AES_GCM || mode == NX_MODE_AES_CCM)
		nx_ctx->kmem_len = (4 * NX_PAGE_SIZE) +
				   sizeof(struct nx_csbcpb);
	else
		nx_ctx->kmem_len = (3 * NX_PAGE_SIZE) +
				   sizeof(struct nx_csbcpb);

	nx_ctx->kmem = kmalloc(nx_ctx->kmem_len, GFP_KERNEL);
	if (!nx_ctx->kmem)
		return -ENOMEM;

	/* the csbcpb and scatterlists must be 4K aligned pages */
	nx_ctx->csbcpb = (struct nx_csbcpb *)(round_up((u64)nx_ctx->kmem,
						       (u64)NX_PAGE_SIZE));
	nx_ctx->in_sg = (struct nx_sg *)((u8 *)nx_ctx->csbcpb + NX_PAGE_SIZE);
	nx_ctx->out_sg = (struct nx_sg *)((u8 *)nx_ctx->in_sg + NX_PAGE_SIZE);

	if (mode == NX_MODE_AES_GCM || mode == NX_MODE_AES_CCM)
		nx_ctx->csbcpb_aead =
			(struct nx_csbcpb *)((u8 *)nx_ctx->out_sg +
					     NX_PAGE_SIZE);

	/* give each context a pointer to global stats and their OF
	 * properties */
	nx_ctx->stats = &nx_driver.stats;
	memcpy(nx_ctx->props, nx_driver.of.ap[fc][mode],
	       sizeof(struct alg_props) * 3);

	return 0;
}