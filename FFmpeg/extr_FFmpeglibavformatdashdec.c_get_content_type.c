#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ xmlNodePtr ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;

/* Variables and functions */
 int AVMEDIA_TYPE_AUDIO ; 
 int AVMEDIA_TYPE_SUBTITLE ; 
 int AVMEDIA_TYPE_UNKNOWN ; 
 int AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ av_stristr (char const*,char*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 char* xmlGetProp (scalar_t__,char const*) ; 

__attribute__((used)) static enum AVMediaType get_content_type(xmlNodePtr node)
{
    enum AVMediaType type = AVMEDIA_TYPE_UNKNOWN;
    int i = 0;
    const char *attr;
    char *val = NULL;

    if (node) {
        for (i = 0; i < 2; i++) {
            attr = i ? "mimeType" : "contentType";
            val = xmlGetProp(node, attr);
            if (val) {
                if (av_stristr((const char *)val, "video")) {
                    type = AVMEDIA_TYPE_VIDEO;
                } else if (av_stristr((const char *)val, "audio")) {
                    type = AVMEDIA_TYPE_AUDIO;
                } else if (av_stristr((const char *)val, "text")) {
                    type = AVMEDIA_TYPE_SUBTITLE;
                }
                xmlFree(val);
            }
        }
    }
    return type;
}