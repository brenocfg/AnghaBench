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
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int DXVA_CONTEXT_CFG_BITSTREAM (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int is_slice_short(const AVCodecContext *avctx, AVDXVAContext *ctx)
{
    assert(DXVA_CONTEXT_CFG_BITSTREAM(avctx, ctx) == 1 ||
           DXVA_CONTEXT_CFG_BITSTREAM(avctx, ctx) == 2);
    return DXVA_CONTEXT_CFG_BITSTREAM(avctx, ctx) == 2;
}