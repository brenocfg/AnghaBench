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
struct section {int flags; } ;
struct TYPE_4__ {size_t level; struct section** section; TYPE_2__* priv; } ;
typedef  TYPE_1__ WriterContext ;
struct TYPE_5__ {char* item_start_end; int /*<<< orphan*/  compact; int /*<<< orphan*/  indent_level; } ;
typedef  TYPE_2__ JSONContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_INDENT () ; 
 int SECTION_FLAG_IS_ARRAY ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void json_print_section_footer(WriterContext *wctx)
{
    JSONContext *json = wctx->priv;
    const struct section *section = wctx->section[wctx->level];

    if (wctx->level == 0) {
        json->indent_level--;
        printf("\n}\n");
    } else if (section->flags & SECTION_FLAG_IS_ARRAY) {
        printf("\n");
        json->indent_level--;
        JSON_INDENT();
        printf("]");
    } else {
        printf("%s", json->item_start_end);
        json->indent_level--;
        if (!json->compact)
            JSON_INDENT();
        printf("}");
    }
}