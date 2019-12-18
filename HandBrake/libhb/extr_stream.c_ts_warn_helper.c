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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_3__ {int errors; int frames; int last_error_frame; int last_error_count; } ;
typedef  TYPE_1__ hb_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_log (char*,int,...) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts_warn_helper( hb_stream_t *stream, char *log, va_list args )
{
    // limit error printing to at most one per minute of video (at 30fps)
    ++stream->errors;
    if ( stream->frames - stream->last_error_frame >= 30*60 )
    {
        char msg[256];

        vsnprintf( msg, sizeof(msg), log, args );

        if ( stream->errors - stream->last_error_count < 10 )
        {
            hb_log( "stream: error near frame %d: %s", stream->frames, msg );
        }
        else
        {
            int Edelta = stream->errors - stream->last_error_count;
            double Epcnt = (double)Edelta * 100. /
                            (stream->frames - stream->last_error_frame);
            hb_log( "stream: %d new errors (%.0f%%) up to frame %d: %s",
                    Edelta, Epcnt, stream->frames, msg );
        }
        stream->last_error_frame = stream->frames;
        stream->last_error_count = stream->errors;
    }
}