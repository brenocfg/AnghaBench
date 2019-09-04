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
struct TYPE_4__ {int within_tag; int /*<<< orphan*/  indent_level; scalar_t__ fully_qualified; } ;
typedef  TYPE_1__ XMLContext ;
struct TYPE_5__ {size_t level; scalar_t__* nb_item; struct section** section; TYPE_1__* priv; } ;
typedef  TYPE_2__ WriterContext ;

/* Variables and functions */
 int SECTION_FLAG_HAS_VARIABLE_FIELDS ; 
 int SECTION_FLAG_IS_ARRAY ; 
 int SECTION_FLAG_IS_WRAPPER ; 
 int /*<<< orphan*/  XML_INDENT () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void xml_print_section_header(WriterContext *wctx)
{
    XMLContext *xml = wctx->priv;
    const struct section *section = wctx->section[wctx->level];
    const struct section *parent_section = wctx->level ?
        wctx->section[wctx->level-1] : NULL;

    if (wctx->level == 0) {
        const char *qual = " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' "
            "xmlns:ffprobe='http://www.ffmpeg.org/schema/ffprobe' "
            "xsi:schemaLocation='http://www.ffmpeg.org/schema/ffprobe ffprobe.xsd'";

        printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        printf("<%sffprobe%s>\n",
               xml->fully_qualified ? "ffprobe:" : "",
               xml->fully_qualified ? qual : "");
        return;
    }

    if (xml->within_tag) {
        xml->within_tag = 0;
        printf(">\n");
    }
    if (section->flags & SECTION_FLAG_HAS_VARIABLE_FIELDS) {
        xml->indent_level++;
    } else {
        if (parent_section && (parent_section->flags & SECTION_FLAG_IS_WRAPPER) &&
            wctx->level && wctx->nb_item[wctx->level-1])
            printf("\n");
        xml->indent_level++;

        if (section->flags & SECTION_FLAG_IS_ARRAY) {
            XML_INDENT(); printf("<%s>\n", section->name);
        } else {
            XML_INDENT(); printf("<%s ", section->name);
            xml->within_tag = 1;
        }
    }
}