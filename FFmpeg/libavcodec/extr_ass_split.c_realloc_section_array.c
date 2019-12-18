#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int offset_count; int offset; int size; } ;
struct TYPE_5__ {size_t current_section; int /*<<< orphan*/  ass; } ;
typedef  TYPE_1__ ASSSplitContext ;
typedef  TYPE_2__ ASSSection ;

/* Variables and functions */
 TYPE_2__* ass_sections ; 
 int /*<<< orphan*/ * av_realloc_array (void*,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t *realloc_section_array(ASSSplitContext *ctx)
{
    const ASSSection *section = &ass_sections[ctx->current_section];
    int *count = (int *)((uint8_t *)&ctx->ass + section->offset_count);
    void **section_ptr = (void **)((uint8_t *)&ctx->ass + section->offset);
    uint8_t *tmp = av_realloc_array(*section_ptr, (*count+1), section->size);
    if (!tmp)
        return NULL;
    *section_ptr = tmp;
    tmp += *count * section->size;
    memset(tmp, 0, section->size);
    (*count)++;
    return tmp;
}