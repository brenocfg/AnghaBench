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
struct TYPE_5__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  temporal_unit; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVCodecParserContext ;
typedef  TYPE_2__ AV1ParseContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_cbs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_fragment_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void av1_parser_close(AVCodecParserContext *ctx)
{
    AV1ParseContext *s = ctx->priv_data;

    ff_cbs_fragment_free(s->cbc, &s->temporal_unit);
    ff_cbs_close(&s->cbc);
}