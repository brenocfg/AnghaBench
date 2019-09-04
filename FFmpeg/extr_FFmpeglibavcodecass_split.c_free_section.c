#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {scalar_t__ type; int offset; scalar_t__ name; } ;
struct TYPE_7__ {int offset; int offset_count; scalar_t__ format_header; TYPE_3__* fields; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int /*<<< orphan*/  ass; } ;
typedef  TYPE_1__ ASSSplitContext ;
typedef  TYPE_2__ ASSSection ;
typedef  TYPE_3__ ASSFields ;

/* Variables and functions */
 scalar_t__ ASS_STR ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_section(ASSSplitContext *ctx, const ASSSection *section)
{
    uint8_t *ptr = (uint8_t *)&ctx->ass + section->offset;
    int i, j, *count, c = 1;

    if (section->format_header) {
        ptr   = *(void **)ptr;
        count = (int *)((uint8_t *)&ctx->ass + section->offset_count);
    } else
        count = &c;

    if (ptr)
        for (i=0; i<*count; i++, ptr += section->size)
            for (j=0; section->fields[j].name; j++) {
                const ASSFields *field = &section->fields[j];
                if (field->type == ASS_STR)
                    av_freep(ptr + field->offset);
            }
    *count = 0;

    if (section->format_header)
        av_freep((uint8_t *)&ctx->ass + section->offset);
}