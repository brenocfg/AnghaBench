#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hb_stream_type; scalar_t__ frames; scalar_t__ errors; } ;
typedef  TYPE_1__ hb_stream_t ;

/* Variables and functions */
 scalar_t__ ffmpeg ; 
 int /*<<< orphan*/  ffmpeg_close (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_log (char*,scalar_t__,scalar_t__,double) ; 
 int /*<<< orphan*/  hb_stream_delete (TYPE_1__*) ; 

void hb_stream_close( hb_stream_t ** _d )
{
    hb_stream_t *stream = * _d;

    if (stream == NULL)
    {
        return;
    }

    if ( stream->hb_stream_type == ffmpeg )
    {
        ffmpeg_close( stream );
        hb_stream_delete( stream );
        *_d = NULL;
        return;
    }

    if ( stream->frames )
    {
        hb_log( "stream: %d good frames, %d errors (%.0f%%)", stream->frames,
                stream->errors, (double)stream->errors * 100. /
                (double)stream->frames );
    }

    hb_stream_delete( stream );
    *_d = NULL;
}