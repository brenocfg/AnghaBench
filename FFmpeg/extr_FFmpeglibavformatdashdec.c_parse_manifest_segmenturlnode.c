#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
struct representation {int /*<<< orphan*/  n_fragments; int /*<<< orphan*/  fragments; struct fragment* init_section; } ;
struct fragment {void* url; } ;
struct TYPE_11__ {TYPE_2__* priv_data; } ;
struct TYPE_10__ {int max_url_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ DASHContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_URL_SIZE ; 
 int /*<<< orphan*/  av_free (struct fragment*) ; 
 int /*<<< orphan*/  av_strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fragment*) ; 
 void* get_Fragment (char*) ; 
 void* get_content_url (TYPE_1__**,int,int,char*,char*,char*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 char* xmlGetProp (TYPE_1__*,char*) ; 

__attribute__((used)) static int parse_manifest_segmenturlnode(AVFormatContext *s, struct representation *rep,
                                         xmlNodePtr fragmenturl_node,
                                         xmlNodePtr *baseurl_nodes,
                                         char *rep_id_val,
                                         char *rep_bandwidth_val)
{
    DASHContext *c = s->priv_data;
    char *initialization_val = NULL;
    char *media_val = NULL;
    char *range_val = NULL;
    int max_url_size = c ? c->max_url_size: MAX_URL_SIZE;

    if (!av_strcasecmp(fragmenturl_node->name, (const char *)"Initialization")) {
        initialization_val = xmlGetProp(fragmenturl_node, "sourceURL");
        range_val = xmlGetProp(fragmenturl_node, "range");
        if (initialization_val || range_val) {
            rep->init_section = get_Fragment(range_val);
            if (!rep->init_section) {
                xmlFree(initialization_val);
                xmlFree(range_val);
                return AVERROR(ENOMEM);
            }
            rep->init_section->url = get_content_url(baseurl_nodes, 4,
                                                     max_url_size,
                                                     rep_id_val,
                                                     rep_bandwidth_val,
                                                     initialization_val);

            if (!rep->init_section->url) {
                av_free(rep->init_section);
                xmlFree(initialization_val);
                xmlFree(range_val);
                return AVERROR(ENOMEM);
            }
            xmlFree(initialization_val);
            xmlFree(range_val);
        }
    } else if (!av_strcasecmp(fragmenturl_node->name, (const char *)"SegmentURL")) {
        media_val = xmlGetProp(fragmenturl_node, "media");
        range_val = xmlGetProp(fragmenturl_node, "mediaRange");
        if (media_val || range_val) {
            struct fragment *seg = get_Fragment(range_val);
            if (!seg) {
                xmlFree(media_val);
                xmlFree(range_val);
                return AVERROR(ENOMEM);
            }
            seg->url = get_content_url(baseurl_nodes, 4,
                                       max_url_size,
                                       rep_id_val,
                                       rep_bandwidth_val,
                                       media_val);
            if (!seg->url) {
                av_free(seg);
                xmlFree(media_val);
                xmlFree(range_val);
                return AVERROR(ENOMEM);
            }
            dynarray_add(&rep->fragments, &rep->n_fragments, seg);
            xmlFree(media_val);
            xmlFree(range_val);
        }
    }

    return 0;
}