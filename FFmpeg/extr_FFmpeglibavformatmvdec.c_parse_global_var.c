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
struct TYPE_6__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {void* nb_audio_tracks; void* nb_video_tracks; } ;
typedef  TYPE_1__ MvContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* var_read_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  var_read_metadata (TYPE_2__*,char const*,int) ; 

__attribute__((used)) static int parse_global_var(AVFormatContext *avctx, AVStream *st,
                            const char *name, int size)
{
    MvContext *mv = avctx->priv_data;
    AVIOContext *pb = avctx->pb;
    if (!strcmp(name, "__NUM_I_TRACKS")) {
        mv->nb_video_tracks = var_read_int(pb, size);
    } else if (!strcmp(name, "__NUM_A_TRACKS")) {
        mv->nb_audio_tracks = var_read_int(pb, size);
    } else if (!strcmp(name, "COMMENT") || !strcmp(name, "TITLE")) {
        var_read_metadata(avctx, name, size);
    } else if (!strcmp(name, "LOOP_MODE") || !strcmp(name, "NUM_LOOPS") ||
               !strcmp(name, "OPTIMIZED")) {
        avio_skip(pb, size); // ignore
    } else
        return AVERROR_INVALIDDATA;

    return 0;
}