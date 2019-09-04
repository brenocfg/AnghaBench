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
struct TYPE_8__ {int styles_count; TYPE_1__* styles; } ;
struct TYPE_7__ {TYPE_3__ ass; } ;
struct TYPE_6__ {scalar_t__ name; } ;
typedef  TYPE_1__ ASSStyle ;
typedef  TYPE_2__ ASSSplitContext ;
typedef  TYPE_3__ ASS ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

ASSStyle *ff_ass_style_get(ASSSplitContext *ctx, const char *style)
{
    ASS *ass = &ctx->ass;
    int i;

    if (!style || !*style)
        style = "Default";
    for (i=0; i<ass->styles_count; i++)
        if (ass->styles[i].name && !strcmp(ass->styles[i].name, style))
            return ass->styles + i;
    return NULL;
}