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
struct TYPE_3__ {int /*<<< orphan*/  dma_qstatus_R; } ;
struct TYPE_4__ {TYPE_1__ prob; } ;
struct spu_context {TYPE_2__ csa; } ;

/* Variables and functions */

__attribute__((used)) static u32 spu_backing_get_mfc_free_elements(struct spu_context *ctx)
{
	return ctx->csa.prob.dma_qstatus_R;
}