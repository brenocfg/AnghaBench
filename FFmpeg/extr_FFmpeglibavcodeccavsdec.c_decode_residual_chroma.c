#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cbp; size_t qp; int /*<<< orphan*/  c_stride; int /*<<< orphan*/  cv; int /*<<< orphan*/  gb; int /*<<< orphan*/  cu; } ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 int /*<<< orphan*/  chroma_dec ; 
 int decode_residual_block (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_cavs_chroma_qp ; 

__attribute__((used)) static inline int decode_residual_chroma(AVSContext *h)
{
    if (h->cbp & (1 << 4)) {
        int ret = decode_residual_block(h, &h->gb, chroma_dec, 0,
                              ff_cavs_chroma_qp[h->qp], h->cu, h->c_stride);
        if (ret < 0)
            return ret;
    }
    if (h->cbp & (1 << 5)) {
        int ret = decode_residual_block(h, &h->gb, chroma_dec, 0,
                              ff_cavs_chroma_qp[h->qp], h->cv, h->c_stride);
        if (ret < 0)
            return ret;
    }
    return 0;
}