#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct section {int flags; char const* element_name; } ;
typedef  int /*<<< orphan*/  XMLContext ;
struct TYPE_4__ {size_t level; scalar_t__* nb_item; struct section** section; int /*<<< orphan*/ * priv; } ;
typedef  TYPE_1__ WriterContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int SECTION_FLAG_HAS_VARIABLE_FIELDS ; 
 int /*<<< orphan*/  XML_INDENT () ; 
 int /*<<< orphan*/  av_bprint_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* xml_escape_str (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 

__attribute__((used)) static void xml_print_str(WriterContext *wctx, const char *key, const char *value)
{
    AVBPrint buf;
    XMLContext *xml = wctx->priv;
    const struct section *section = wctx->section[wctx->level];

    av_bprint_init(&buf, 1, AV_BPRINT_SIZE_UNLIMITED);

    if (section->flags & SECTION_FLAG_HAS_VARIABLE_FIELDS) {
        XML_INDENT();
        printf("<%s key=\"%s\"",
               section->element_name, xml_escape_str(&buf, key, wctx));
        av_bprint_clear(&buf);
        printf(" value=\"%s\"/>\n", xml_escape_str(&buf, value, wctx));
    } else {
        if (wctx->nb_item[wctx->level])
            printf(" ");
        printf("%s=\"%s\"", key, xml_escape_str(&buf, value, wctx));
    }

    av_bprint_finalize(&buf, NULL);
}