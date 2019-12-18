#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  fragment; int /*<<< orphan*/  type_list; } ;
typedef  TYPE_1__ FilterUnitsContext ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_fragment_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void filter_units_close(AVBSFContext *bsf)
{
    FilterUnitsContext *ctx = bsf->priv_data;

    av_freep(&ctx->type_list);

    ff_cbs_fragment_free(ctx->cbc, &ctx->fragment);
    ff_cbs_close(&ctx->cbc);
}