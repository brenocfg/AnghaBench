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
struct section {int flags; char* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  indent_level; scalar_t__ within_tag; scalar_t__ fully_qualified; } ;
typedef  TYPE_1__ XMLContext ;
struct TYPE_5__ {size_t level; struct section** section; TYPE_1__* priv; } ;
typedef  TYPE_2__ WriterContext ;

/* Variables and functions */
 int SECTION_FLAG_HAS_VARIABLE_FIELDS ; 
 int /*<<< orphan*/  XML_INDENT () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void xml_print_section_footer(WriterContext *wctx)
{
    XMLContext *xml = wctx->priv;
    const struct section *section = wctx->section[wctx->level];

    if (wctx->level == 0) {
        printf("</%sffprobe>\n", xml->fully_qualified ? "ffprobe:" : "");
    } else if (xml->within_tag) {
        xml->within_tag = 0;
        printf("/>\n");
        xml->indent_level--;
    } else if (section->flags & SECTION_FLAG_HAS_VARIABLE_FIELDS) {
        xml->indent_level--;
    } else {
        XML_INDENT(); printf("</%s>\n", section->name);
        xml->indent_level--;
    }
}