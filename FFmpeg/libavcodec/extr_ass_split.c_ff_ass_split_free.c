#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * field_order; } ;
typedef  TYPE_1__ ASSSplitContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ass_sections ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_section (TYPE_1__*,int /*<<< orphan*/ *) ; 

void ff_ass_split_free(ASSSplitContext *ctx)
{
    if (ctx) {
        int i;
        for (i=0; i<FF_ARRAY_ELEMS(ass_sections); i++) {
            free_section(ctx, &ass_sections[i]);
            av_freep(&(ctx->field_order[i]));
        }
        av_free(ctx);
    }
}