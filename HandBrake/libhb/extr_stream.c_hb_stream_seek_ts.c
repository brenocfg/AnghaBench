#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {scalar_t__ hb_stream_type; } ;
typedef  TYPE_1__ hb_stream_t ;

/* Variables and functions */
 scalar_t__ ffmpeg ; 
 int ffmpeg_seek_ts (TYPE_1__*,int /*<<< orphan*/ ) ; 

int hb_stream_seek_ts( hb_stream_t * stream, int64_t ts )
{
    if ( stream->hb_stream_type == ffmpeg )
    {
        return ffmpeg_seek_ts( stream, ts );
    }
    return -1;
}