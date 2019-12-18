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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_netobj {int dummy; } ;
struct xdr_buf {int dummy; } ;
struct spkm3_ctx {int dummy; } ;
struct gss_ctx {struct spkm3_ctx* internal_ctx_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPKM_MIC_TOK ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spkm3_make_token (struct spkm3_ctx*,struct xdr_buf*,struct xdr_netobj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
gss_get_mic_spkm3(struct gss_ctx	*ctx,
		     struct xdr_buf	*message_buffer,
		     struct xdr_netobj	*message_token)
{
	u32 err = 0;
	struct spkm3_ctx *sctx = ctx->internal_ctx_id;

	err = spkm3_make_token(sctx, message_buffer,
				message_token, SPKM_MIC_TOK);
	dprintk("RPC:       gss_get_mic_spkm3 returning %d\n", err);
	return err;
}