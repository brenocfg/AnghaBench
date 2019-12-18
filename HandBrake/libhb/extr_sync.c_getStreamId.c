#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* subtitle; } ;
struct TYPE_10__ {TYPE_2__* audio; } ;
struct TYPE_8__ {int id; } ;
struct TYPE_13__ {int type; TYPE_5__ subtitle; TYPE_3__ audio; TYPE_1__ video; } ;
typedef  TYPE_6__ sync_stream_t ;
struct TYPE_11__ {int id; } ;
struct TYPE_9__ {int id; } ;

/* Variables and functions */
#define  SYNC_TYPE_AUDIO 130 
#define  SYNC_TYPE_SUBTITLE 129 
#define  SYNC_TYPE_VIDEO 128 

__attribute__((used)) static int getStreamId( sync_stream_t * stream )
{
    switch (stream->type)
    {
        case SYNC_TYPE_VIDEO:
            return stream->video.id;
        case SYNC_TYPE_AUDIO:
            return stream->audio.audio->id;
        case SYNC_TYPE_SUBTITLE:
            return stream->subtitle.subtitle->id;
        default:
            return -1;
    }
}