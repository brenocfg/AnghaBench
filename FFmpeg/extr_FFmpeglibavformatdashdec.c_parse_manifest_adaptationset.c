#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_29__ {TYPE_2__* priv_data; } ;
struct TYPE_28__ {void* adaptionset_bitstreamswitching_val; void* adaptionset_segmentalignment_val; void* adaptionset_maxframerate_val; void* adaptionset_minframerate_val; void* adaptionset_maxheight_val; void* adaptionset_minheight_val; void* adaptionset_maxwidth_val; void* adaptionset_minwidth_val; void* adaptionset_maxbw_val; void* adaptionset_minbw_val; void* adaptionset_lang_val; void* adaptionset_par_val; void* adaptionset_contenttype_val; } ;
struct TYPE_27__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ DASHContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int parse_manifest_representation (TYPE_3__*,char const*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* xmlFirstElementChild (TYPE_1__*) ; 
 void* xmlGetProp (TYPE_1__*,char*) ; 
 TYPE_1__* xmlNextElementSibling (TYPE_1__*) ; 

__attribute__((used)) static int parse_manifest_adaptationset(AVFormatContext *s, const char *url,
                                        xmlNodePtr adaptionset_node,
                                        xmlNodePtr mpd_baseurl_node,
                                        xmlNodePtr period_baseurl_node,
                                        xmlNodePtr period_segmenttemplate_node,
                                        xmlNodePtr period_segmentlist_node)
{
    int ret = 0;
    DASHContext *c = s->priv_data;
    xmlNodePtr fragment_template_node = NULL;
    xmlNodePtr content_component_node = NULL;
    xmlNodePtr adaptionset_baseurl_node = NULL;
    xmlNodePtr adaptionset_segmentlist_node = NULL;
    xmlNodePtr adaptionset_supplementalproperty_node = NULL;
    xmlNodePtr node = NULL;
    c->adaptionset_contenttype_val = xmlGetProp(adaptionset_node, "contentType");
    c->adaptionset_par_val = xmlGetProp(adaptionset_node, "par");
    c->adaptionset_lang_val = xmlGetProp(adaptionset_node, "lang");
    c->adaptionset_minbw_val = xmlGetProp(adaptionset_node, "minBandwidth");
    c->adaptionset_maxbw_val = xmlGetProp(adaptionset_node, "maxBandwidth");
    c->adaptionset_minwidth_val = xmlGetProp(adaptionset_node, "minWidth");
    c->adaptionset_maxwidth_val = xmlGetProp(adaptionset_node, "maxWidth");
    c->adaptionset_minheight_val = xmlGetProp(adaptionset_node, "minHeight");
    c->adaptionset_maxheight_val = xmlGetProp(adaptionset_node, "maxHeight");
    c->adaptionset_minframerate_val = xmlGetProp(adaptionset_node, "minFrameRate");
    c->adaptionset_maxframerate_val = xmlGetProp(adaptionset_node, "maxFrameRate");
    c->adaptionset_segmentalignment_val = xmlGetProp(adaptionset_node, "segmentAlignment");
    c->adaptionset_bitstreamswitching_val = xmlGetProp(adaptionset_node, "bitstreamSwitching");

    node = xmlFirstElementChild(adaptionset_node);
    while (node) {
        if (!av_strcasecmp(node->name, (const char *)"SegmentTemplate")) {
            fragment_template_node = node;
        } else if (!av_strcasecmp(node->name, (const char *)"ContentComponent")) {
            content_component_node = node;
        } else if (!av_strcasecmp(node->name, (const char *)"BaseURL")) {
            adaptionset_baseurl_node = node;
        } else if (!av_strcasecmp(node->name, (const char *)"SegmentList")) {
            adaptionset_segmentlist_node = node;
        } else if (!av_strcasecmp(node->name, (const char *)"SupplementalProperty")) {
            adaptionset_supplementalproperty_node = node;
        } else if (!av_strcasecmp(node->name, (const char *)"Representation")) {
            ret = parse_manifest_representation(s, url, node,
                                                adaptionset_node,
                                                mpd_baseurl_node,
                                                period_baseurl_node,
                                                period_segmenttemplate_node,
                                                period_segmentlist_node,
                                                fragment_template_node,
                                                content_component_node,
                                                adaptionset_baseurl_node,
                                                adaptionset_segmentlist_node,
                                                adaptionset_supplementalproperty_node);
            if (ret < 0) {
                return ret;
            }
        }
        node = xmlNextElementSibling(node);
    }
    return 0;
}