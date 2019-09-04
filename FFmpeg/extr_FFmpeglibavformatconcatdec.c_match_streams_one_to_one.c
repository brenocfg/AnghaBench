#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nb_streams; int /*<<< orphan*/ ** streams; TYPE_4__* priv_data; } ;
struct TYPE_11__ {TYPE_3__* cur_file; TYPE_1__* avf; } ;
struct TYPE_10__ {int nb_streams; TYPE_2__* streams; } ;
struct TYPE_9__ {int out_stream_index; } ;
struct TYPE_8__ {int nb_streams; int /*<<< orphan*/ * streams; } ;
typedef  TYPE_4__ ConcatContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int copy_stream_props (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_streams_one_to_one(AVFormatContext *avf)
{
    ConcatContext *cat = avf->priv_data;
    AVStream *st;
    int i, ret;

    for (i = cat->cur_file->nb_streams; i < cat->avf->nb_streams; i++) {
        if (i < avf->nb_streams) {
            st = avf->streams[i];
        } else {
            if (!(st = avformat_new_stream(avf, NULL)))
                return AVERROR(ENOMEM);
        }
        if ((ret = copy_stream_props(st, cat->avf->streams[i])) < 0)
            return ret;
        cat->cur_file->streams[i].out_stream_index = i;
    }
    return 0;
}