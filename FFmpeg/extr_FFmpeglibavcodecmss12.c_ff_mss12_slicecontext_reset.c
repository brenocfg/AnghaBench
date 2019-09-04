#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  inter_pix_ctx; int /*<<< orphan*/  intra_pix_ctx; int /*<<< orphan*/  pivot; int /*<<< orphan*/  edge_mode; int /*<<< orphan*/  split_mode; int /*<<< orphan*/  inter_region; int /*<<< orphan*/  intra_region; } ;
typedef  TYPE_1__ SliceContext ;

/* Variables and functions */
 int /*<<< orphan*/  model_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixctx_reset (int /*<<< orphan*/ *) ; 

void ff_mss12_slicecontext_reset(SliceContext *sc)
{
    model_reset(&sc->intra_region);
    model_reset(&sc->inter_region);
    model_reset(&sc->split_mode);
    model_reset(&sc->edge_mode);
    model_reset(&sc->pivot);
    pixctx_reset(&sc->intra_pix_ctx);
    pixctx_reset(&sc->inter_pix_ctx);
}