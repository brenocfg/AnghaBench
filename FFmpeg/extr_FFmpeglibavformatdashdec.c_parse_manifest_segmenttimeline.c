#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  TYPE_2__* xmlAttrPtr ;
struct timeline {void* duration; void* repeat; void* starttime; } ;
struct representation {int /*<<< orphan*/  n_timelines; int /*<<< orphan*/  timelines; } ;
typedef  void* int64_t ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_2__* properties; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct timeline* av_mallocz (int) ; 
 int /*<<< orphan*/  av_strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeline*) ; 
 scalar_t__ strtoll (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 char* xmlGetProp (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_manifest_segmenttimeline(AVFormatContext *s, struct representation *rep,
                                          xmlNodePtr fragment_timeline_node)
{
    xmlAttrPtr attr = NULL;
    char *val  = NULL;

    if (!av_strcasecmp(fragment_timeline_node->name, (const char *)"S")) {
        struct timeline *tml = av_mallocz(sizeof(struct timeline));
        if (!tml) {
            return AVERROR(ENOMEM);
        }
        attr = fragment_timeline_node->properties;
        while (attr) {
            val = xmlGetProp(fragment_timeline_node, attr->name);

            if (!val) {
                av_log(s, AV_LOG_WARNING, "parse_manifest_segmenttimeline attr->name = %s val is NULL\n", attr->name);
                continue;
            }

            if (!av_strcasecmp(attr->name, (const char *)"t")) {
                tml->starttime = (int64_t)strtoll(val, NULL, 10);
            } else if (!av_strcasecmp(attr->name, (const char *)"r")) {
                tml->repeat =(int64_t) strtoll(val, NULL, 10);
            } else if (!av_strcasecmp(attr->name, (const char *)"d")) {
                tml->duration = (int64_t)strtoll(val, NULL, 10);
            }
            attr = attr->next;
            xmlFree(val);
        }
        dynarray_add(&rep->timelines, &rep->n_timelines, tml);
    }

    return 0;
}