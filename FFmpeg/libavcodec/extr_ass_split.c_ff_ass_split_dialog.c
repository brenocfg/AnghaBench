#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  section; } ;
struct TYPE_9__ {int dialogs_count; int /*<<< orphan*/ * dialogs; } ;
struct TYPE_10__ {TYPE_1__ ass; } ;
typedef  TYPE_2__ ASSSplitContext ;
typedef  int /*<<< orphan*/  ASSDialog ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_4__*) ; 
 TYPE_4__* ass_sections ; 
 scalar_t__ ass_split (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  free_section (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

ASSDialog *ff_ass_split_dialog(ASSSplitContext *ctx, const char *buf,
                               int cache, int *number)
{
    ASSDialog *dialog = NULL;
    int i, count;
    if (!cache)
        for (i=0; i<FF_ARRAY_ELEMS(ass_sections); i++)
            if (!strcmp(ass_sections[i].section, "Events")) {
                free_section(ctx, &ass_sections[i]);
                break;
            }
    count = ctx->ass.dialogs_count;
    if (ass_split(ctx, buf) == 0)
        dialog = ctx->ass.dialogs + count;
    if (number)
        *number = ctx->ass.dialogs_count - count;
    return dialog;
}