#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ sync_stream_t ;

/* Variables and functions */
#define  SYNC_TYPE_AUDIO 130 
#define  SYNC_TYPE_SUBTITLE 129 
#define  SYNC_TYPE_VIDEO 128 

__attribute__((used)) static const char * getStreamType( sync_stream_t * stream )
{
    switch (stream->type)
    {
        case SYNC_TYPE_VIDEO:
            return "Video";
        case SYNC_TYPE_AUDIO:
            return "Audio";
        case SYNC_TYPE_SUBTITLE:
            return "Subtitle";
        default:
            return "Unknown";
    }
}