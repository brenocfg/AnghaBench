#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t level; TYPE_1__** section; TYPE_3__* priv; } ;
typedef  TYPE_2__ WriterContext ;
struct TYPE_7__ {scalar_t__* terminate_line; int /*<<< orphan*/ * nested_section; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_3__ CompactContext ;

/* Variables and functions */
 int SECTION_FLAG_IS_ARRAY ; 
 int SECTION_FLAG_IS_WRAPPER ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void compact_print_section_footer(WriterContext *wctx)
{
    CompactContext *compact = wctx->priv;

    if (!compact->nested_section[wctx->level] &&
        compact->terminate_line[wctx->level] &&
        !(wctx->section[wctx->level]->flags & (SECTION_FLAG_IS_WRAPPER|SECTION_FLAG_IS_ARRAY)))
        printf("\n");
}