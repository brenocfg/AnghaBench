#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__* priv_data; } ;
struct TYPE_16__ {int stream_match_mode; TYPE_2__* avf; TYPE_1__* cur_file; } ;
struct TYPE_15__ {int out_stream_index; } ;
struct TYPE_14__ {int nb_streams; } ;
struct TYPE_13__ {int nb_streams; TYPE_3__* streams; } ;
typedef  TYPE_3__ ConcatStream ;
typedef  TYPE_4__ ConcatContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  MATCH_EXACT_ID 129 
#define  MATCH_ONE_TO_ONE 128 
 TYPE_3__* av_realloc (TYPE_3__*,int) ; 
 int detect_stream_specific (TYPE_5__*,int) ; 
 int match_streams_exact_id (TYPE_5__*) ; 
 int match_streams_one_to_one (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int match_streams(AVFormatContext *avf)
{
    ConcatContext *cat = avf->priv_data;
    ConcatStream *map;
    int i, ret;

    if (cat->cur_file->nb_streams >= cat->avf->nb_streams)
        return 0;
    map = av_realloc(cat->cur_file->streams,
                     cat->avf->nb_streams * sizeof(*map));
    if (!map)
        return AVERROR(ENOMEM);
    cat->cur_file->streams = map;
    memset(map + cat->cur_file->nb_streams, 0,
           (cat->avf->nb_streams - cat->cur_file->nb_streams) * sizeof(*map));

    for (i = cat->cur_file->nb_streams; i < cat->avf->nb_streams; i++) {
        map[i].out_stream_index = -1;
        if ((ret = detect_stream_specific(avf, i)) < 0)
            return ret;
    }
    switch (cat->stream_match_mode) {
    case MATCH_ONE_TO_ONE:
        ret = match_streams_one_to_one(avf);
        break;
    case MATCH_EXACT_ID:
        ret = match_streams_exact_id(avf);
        break;
    default:
        ret = AVERROR_BUG;
    }
    if (ret < 0)
        return ret;
    cat->cur_file->nb_streams = cat->avf->nb_streams;
    return 0;
}