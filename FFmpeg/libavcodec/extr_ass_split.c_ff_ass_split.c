#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int current_section; } ;
typedef  TYPE_1__ ASSSplitContext ;

/* Variables and functions */
 scalar_t__ ass_split (TYPE_1__*,char const*) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  ff_ass_split_free (TYPE_1__*) ; 

ASSSplitContext *ff_ass_split(const char *buf)
{
    ASSSplitContext *ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return NULL;
    ctx->current_section = -1;
    if (ass_split(ctx, buf) < 0) {
        ff_ass_split_free(ctx);
        return NULL;
    }
    return ctx;
}