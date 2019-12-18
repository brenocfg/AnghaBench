#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int packetsize; int /*<<< orphan*/  hb_stream_type; int /*<<< orphan*/  file_handle; } ;
typedef  TYPE_1__ hb_stream_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  hb_ps_stream_init (TYPE_1__*) ; 
 scalar_t__ hb_stream_check_for_ps (TYPE_1__*) ; 
 int hb_stream_check_for_ts (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_ts_stream_init (TYPE_1__*) ; 
 int /*<<< orphan*/  program ; 
 int /*<<< orphan*/  transport ; 

__attribute__((used)) static int hb_stream_get_type(hb_stream_t *stream)
{
    uint8_t buf[2048*4];

    if ( fread(buf, 1, sizeof(buf), stream->file_handle) == sizeof(buf) )
    {
        int psize;
        if ( ( psize = hb_stream_check_for_ts(buf) ) != 0 )
        {
            int offset = psize >> 8;
            psize &= 0xff;
            hb_log("file is MPEG Transport Stream with %d byte packets"
                   " offset %d bytes", psize, offset);
            stream->packetsize = psize;
            stream->hb_stream_type = transport;
            if (hb_ts_stream_init(stream) == 0)
                return 1;
        }
        else if ( hb_stream_check_for_ps(stream) != 0 )
        {
            hb_log("file is MPEG Program Stream");
            stream->hb_stream_type = program;
            hb_ps_stream_init(stream);
            // We default to mpeg codec for ps streams if no
            // video found in program stream map
            return 1;
        }
    }
    return 0;
}