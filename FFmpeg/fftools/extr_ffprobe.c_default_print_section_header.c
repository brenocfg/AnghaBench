#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct section {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  element_name; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {size_t level; TYPE_4__* section_pbuf; struct section** section; TYPE_2__* priv; } ;
typedef  TYPE_1__ WriterContext ;
struct TYPE_8__ {int /*<<< orphan*/  str; } ;
struct TYPE_7__ {int* nested_section; scalar_t__ noprint_wrappers; } ;
typedef  TYPE_2__ DefaultContext ;

/* Variables and functions */
 int SECTION_FLAG_IS_ARRAY ; 
 int SECTION_FLAG_IS_WRAPPER ; 
 int /*<<< orphan*/  av_bprint_clear (TYPE_4__*) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_4__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_x_if_null (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* upcase_string (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void default_print_section_header(WriterContext *wctx)
{
    DefaultContext *def = wctx->priv;
    char buf[32];
    const struct section *section = wctx->section[wctx->level];
    const struct section *parent_section = wctx->level ?
        wctx->section[wctx->level-1] : NULL;

    av_bprint_clear(&wctx->section_pbuf[wctx->level]);
    if (parent_section &&
        !(parent_section->flags & (SECTION_FLAG_IS_WRAPPER|SECTION_FLAG_IS_ARRAY))) {
        def->nested_section[wctx->level] = 1;
        av_bprintf(&wctx->section_pbuf[wctx->level], "%s%s:",
                   wctx->section_pbuf[wctx->level-1].str,
                   upcase_string(buf, sizeof(buf),
                                 av_x_if_null(section->element_name, section->name)));
    }

    if (def->noprint_wrappers || def->nested_section[wctx->level])
        return;

    if (!(section->flags & (SECTION_FLAG_IS_WRAPPER|SECTION_FLAG_IS_ARRAY)))
        printf("[%s]\n", upcase_string(buf, sizeof(buf), section->name));
}