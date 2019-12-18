#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_9__ {int track_ids_ok; int nb_streams; int flags; TYPE_2__* tracks; scalar_t__ use_stream_ids_as_track_ids; } ;
struct TYPE_8__ {scalar_t__ entry; int track_id; } ;
struct TYPE_7__ {int id; } ;
typedef  TYPE_3__ MOVMuxContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int FF_MOV_FLAG_FRAGMENT ; 

__attribute__((used)) static int mov_setup_track_ids(MOVMuxContext *mov, AVFormatContext *s)
{
    int i;

    if (mov->track_ids_ok)
        return 0;

    if (mov->use_stream_ids_as_track_ids) {
        int next_generated_track_id = 0;
        for (i = 0; i < s->nb_streams; i++) {
            if (s->streams[i]->id > next_generated_track_id)
                next_generated_track_id = s->streams[i]->id;
        }

        for (i = 0; i < mov->nb_streams; i++) {
            if (mov->tracks[i].entry <= 0 && !(mov->flags & FF_MOV_FLAG_FRAGMENT))
                continue;

            mov->tracks[i].track_id = i >= s->nb_streams ? ++next_generated_track_id : s->streams[i]->id;
        }
    } else {
        for (i = 0; i < mov->nb_streams; i++) {
            if (mov->tracks[i].entry <= 0 && !(mov->flags & FF_MOV_FLAG_FRAGMENT))
                continue;

            mov->tracks[i].track_id = i + 1;
        }
    }

    mov->track_ids_ok = 1;

    return 0;
}