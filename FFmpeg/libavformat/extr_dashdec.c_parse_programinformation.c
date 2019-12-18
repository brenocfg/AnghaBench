#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_11__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strcasecmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* xmlFirstElementChild (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 TYPE_1__* xmlNextElementSibling (TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlNodeGetContent (TYPE_1__*) ; 

__attribute__((used)) static int parse_programinformation(AVFormatContext *s, xmlNodePtr node)
{
    xmlChar *val = NULL;

    node = xmlFirstElementChild(node);
    while (node) {
        if (!av_strcasecmp(node->name, "Title")) {
            val = xmlNodeGetContent(node);
            if (val) {
                av_dict_set(&s->metadata, "Title", val, 0);
            }
        } else if (!av_strcasecmp(node->name, "Source")) {
            val = xmlNodeGetContent(node);
            if (val) {
                av_dict_set(&s->metadata, "Source", val, 0);
            }
        } else if (!av_strcasecmp(node->name, "Copyright")) {
            val = xmlNodeGetContent(node);
            if (val) {
                av_dict_set(&s->metadata, "Copyright", val, 0);
            }
        }
        node = xmlNextElementSibling(node);
        xmlFree(val);
        val = NULL;
    }
    return 0;
}