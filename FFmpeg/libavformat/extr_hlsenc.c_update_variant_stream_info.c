#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int nb_streams; int /*<<< orphan*/ * streams; int /*<<< orphan*/  ccgroup; scalar_t__ var_stream_idx; } ;
struct TYPE_10__ {unsigned int nb_streams; int /*<<< orphan*/ * streams; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int nb_varstreams; TYPE_7__* var_streams; TYPE_1__* cc_streams; scalar_t__ nb_ccstreams; scalar_t__ var_stream_map; scalar_t__ cc_stream_map; } ;
struct TYPE_8__ {int /*<<< orphan*/  ccgroup; } ;
typedef  TYPE_2__ HLSContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (TYPE_7__**) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  av_strdup (int /*<<< orphan*/ ) ; 
 int parse_cc_stream_mapstring (TYPE_3__*) ; 
 int parse_variant_stream_mapstring (TYPE_3__*) ; 

__attribute__((used)) static int update_variant_stream_info(AVFormatContext *s)
{
    HLSContext *hls = s->priv_data;
    unsigned int i;
    int ret = 0;

    if (hls->cc_stream_map) {
        ret = parse_cc_stream_mapstring(s);
        if (ret < 0)
            return ret;
    }

    if (hls->var_stream_map) {
        return parse_variant_stream_mapstring(s);
    } else {
        //By default, a single variant stream with all the codec streams is created
        hls->nb_varstreams = 1;
        hls->var_streams = av_mallocz(sizeof(*hls->var_streams) *
                                             hls->nb_varstreams);
        if (!hls->var_streams)
            return AVERROR(ENOMEM);

        hls->var_streams[0].var_stream_idx = 0;
        hls->var_streams[0].nb_streams = s->nb_streams;
        hls->var_streams[0].streams = av_mallocz(sizeof(AVStream *) *
                                            hls->var_streams[0].nb_streams);
        if (!hls->var_streams[0].streams) {
            av_freep(&hls->var_streams);
            return AVERROR(ENOMEM);
        }

        //by default, the first available ccgroup is mapped to the variant stream
        if (hls->nb_ccstreams) {
            hls->var_streams[0].ccgroup = av_strdup(hls->cc_streams[0].ccgroup);
            if (!hls->var_streams[0].ccgroup) {
                av_freep(&hls->var_streams);
                return AVERROR(ENOMEM);
            }
        }

        for (i = 0; i < s->nb_streams; i++)
            hls->var_streams[0].streams[i] = s->streams[i];
    }
    return 0;
}