#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {struct TYPE_5__* entries; } ;
struct TYPE_4__ {TYPE_3__* stream_duration_offsets; TYPE_3__* stream_durations; TYPE_3__* tracks; TYPE_3__* attachments; TYPE_3__* cues; TYPE_3__* main_seekhead; scalar_t__ tags_bc; scalar_t__ tracks_bc; scalar_t__ info_bc; scalar_t__ dyn_bc; } ;
typedef  TYPE_1__ MatroskaMuxContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  avio_close_dyn_buf (scalar_t__,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void mkv_free(MatroskaMuxContext *mkv) {
    uint8_t* buf;
    if (mkv->dyn_bc) {
        avio_close_dyn_buf(mkv->dyn_bc, &buf);
        av_free(buf);
    }
    if (mkv->info_bc) {
        avio_close_dyn_buf(mkv->info_bc, &buf);
        av_free(buf);
    }
    if (mkv->tracks_bc) {
        avio_close_dyn_buf(mkv->tracks_bc, &buf);
        av_free(buf);
    }
    if (mkv->tags_bc) {
        avio_close_dyn_buf(mkv->tags_bc, &buf);
        av_free(buf);
    }
    if (mkv->main_seekhead) {
        av_freep(&mkv->main_seekhead->entries);
        av_freep(&mkv->main_seekhead);
    }
    if (mkv->cues) {
        av_freep(&mkv->cues->entries);
        av_freep(&mkv->cues);
    }
    if (mkv->attachments) {
        av_freep(&mkv->attachments->entries);
        av_freep(&mkv->attachments);
    }
    av_freep(&mkv->tracks);
    av_freep(&mkv->stream_durations);
    av_freep(&mkv->stream_duration_offsets);
}