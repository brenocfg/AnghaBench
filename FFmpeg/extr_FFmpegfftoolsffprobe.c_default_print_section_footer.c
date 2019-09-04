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
struct section {int flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {size_t level; struct section** section; TYPE_2__* priv; } ;
typedef  TYPE_1__ WriterContext ;
struct TYPE_5__ {scalar_t__* nested_section; scalar_t__ noprint_wrappers; } ;
typedef  TYPE_2__ DefaultContext ;

/* Variables and functions */
 int SECTION_FLAG_IS_ARRAY ; 
 int SECTION_FLAG_IS_WRAPPER ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* upcase_string (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void default_print_section_footer(WriterContext *wctx)
{
    DefaultContext *def = wctx->priv;
    const struct section *section = wctx->section[wctx->level];
    char buf[32];

    if (def->noprint_wrappers || def->nested_section[wctx->level])
        return;

    if (!(section->flags & (SECTION_FLAG_IS_WRAPPER|SECTION_FLAG_IS_ARRAY)))
        printf("[/%s]\n", upcase_string(buf, sizeof(buf), section->name));
}