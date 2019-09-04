#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ id; } ;
struct TYPE_16__ {int nb_streams; TYPE_8__** streams; TYPE_4__* priv_data; } ;
struct TYPE_15__ {scalar_t__ id; } ;
struct TYPE_14__ {TYPE_3__* cur_file; TYPE_1__* avf; } ;
struct TYPE_13__ {int nb_streams; TYPE_2__* streams; } ;
struct TYPE_12__ {int out_stream_index; } ;
struct TYPE_11__ {int nb_streams; TYPE_5__** streams; } ;
typedef  TYPE_4__ ConcatContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int,int,scalar_t__) ; 
 int copy_stream_props (TYPE_8__*,TYPE_5__*) ; 

__attribute__((used)) static int match_streams_exact_id(AVFormatContext *avf)
{
    ConcatContext *cat = avf->priv_data;
    AVStream *st;
    int i, j, ret;

    for (i = cat->cur_file->nb_streams; i < cat->avf->nb_streams; i++) {
        st = cat->avf->streams[i];
        for (j = 0; j < avf->nb_streams; j++) {
            if (avf->streams[j]->id == st->id) {
                av_log(avf, AV_LOG_VERBOSE,
                       "Match slave stream #%d with stream #%d id 0x%x\n",
                       i, j, st->id);
                if ((ret = copy_stream_props(avf->streams[j], st)) < 0)
                    return ret;
                cat->cur_file->streams[i].out_stream_index = j;
            }
        }
    }
    return 0;
}