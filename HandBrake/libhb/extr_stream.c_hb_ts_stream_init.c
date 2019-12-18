#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {int alloc; int count; TYPE_2__* list; int /*<<< orphan*/  packet; } ;
struct TYPE_15__ {int alloc; TYPE_8__* list; scalar_t__ count; } ;
struct TYPE_18__ {TYPE_3__ ts; TYPE_1__ pes; scalar_t__ scan; int /*<<< orphan*/  packetsize; } ;
typedef  TYPE_4__ hb_stream_t ;
struct TYPE_19__ {int stream_id; int next; } ;
struct TYPE_16__ {int continuity; int pid; int pes_list; scalar_t__ is_pcr; TYPE_13__* buf; } ;
struct TYPE_14__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ A ; 
 scalar_t__ N ; 
 scalar_t__ P ; 
 scalar_t__ S ; 
 scalar_t__ V ; 
 TYPE_13__* hb_buffer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  hb_stream_delete_ts_entry (TYPE_4__*,int) ; 
 int /*<<< orphan*/  hb_ts_resolve_pid_types (TYPE_4__*) ; 
 scalar_t__ hb_ts_stream_find_pids (TYPE_4__*) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_type_name2 (TYPE_4__*,TYPE_8__*) ; 
 scalar_t__ ts_stream_kind (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ts_stream_type (TYPE_4__*,int) ; 

__attribute__((used)) static int hb_ts_stream_init(hb_stream_t *stream)
{
    int i;

    if ( stream->ts.list )
    {
        for (i=0; i < stream->ts.alloc; i++)
        {
            stream->ts.list[i].continuity = -1;
            stream->ts.list[i].pid = -1;
            stream->ts.list[i].pes_list = -1;
        }
    }
    stream->ts.count = 0;

    if ( stream->pes.list )
    {
        for (i=0; i < stream->pes.alloc; i++)
        {
            stream->pes.list[i].stream_id = -1;
            stream->pes.list[i].next = -1;
        }
    }
    stream->pes.count = 0;

    stream->ts.packet = malloc( stream->packetsize );

    // Find the audio and video pids in the stream
    if (hb_ts_stream_find_pids(stream) < 0)
    {
        return -1;
    }

    // hb_ts_resolve_pid_types reads some data, so the TS buffers
    // are needed here.
    for (i = 0; i < stream->ts.count; i++)
    {
        // demuxing buffer for TS to PS conversion
        stream->ts.list[i].buf = hb_buffer_init(stream->packetsize);
        stream->ts.list[i].buf->size = 0;
    }
    hb_ts_resolve_pid_types(stream);

    if( stream->scan )
    {
        hb_log("Found the following PIDS");
        hb_log("    Video PIDS : ");
        for (i=0; i < stream->ts.count; i++)
        {
            if ( ts_stream_kind( stream, i ) == V )
            {
                hb_log( "      0x%x type %s (0x%x)%s",
                        stream->ts.list[i].pid,
                        stream_type_name2(stream,
                                &stream->pes.list[stream->ts.list[i].pes_list]),
                        ts_stream_type( stream, i ),
                        stream->ts.list[i].is_pcr ? " (PCR)" : "");
            }
        }
        hb_log("    Audio PIDS : ");
        for (i = 0; i < stream->ts.count; i++)
        {
            if ( ts_stream_kind( stream, i ) == A )
            {
                hb_log( "      0x%x type %s (0x%x)%s",
                        stream->ts.list[i].pid,
                        stream_type_name2(stream,
                                &stream->pes.list[stream->ts.list[i].pes_list]),
                        ts_stream_type( stream, i ),
                        stream->ts.list[i].is_pcr ? " (PCR)" : "");
            }
        }
        hb_log("    Subtitle PIDS : ");
        for (i = 0; i < stream->ts.count; i++)
        {
            if ( ts_stream_kind( stream, i ) == S )
            {
                hb_log( "      0x%x type %s (0x%x)%s",
                        stream->ts.list[i].pid,
                        stream_type_name2(stream,
                                &stream->pes.list[stream->ts.list[i].pes_list]),
                        ts_stream_type( stream, i ),
                        stream->ts.list[i].is_pcr ? " (PCR)" : "");
            }
        }
        hb_log("    Other PIDS : ");
        for (i = 0; i < stream->ts.count; i++)
        {
            if ( ts_stream_kind( stream, i ) == N ||
                 ts_stream_kind( stream, i ) == P )
            {
                hb_log( "      0x%x type %s (0x%x)%s",
                        stream->ts.list[i].pid,
                        stream_type_name2(stream,
                                &stream->pes.list[stream->ts.list[i].pes_list]),
                        ts_stream_type( stream, i ),
                        stream->ts.list[i].is_pcr ? " (PCR)" : "");
            }
            if ( ts_stream_kind( stream, i ) == N )
                hb_stream_delete_ts_entry(stream, i);
        }
    }
    else
    {
        for (i = 0; i < stream->ts.count; i++)
        {
            if ( ts_stream_kind( stream, i ) == N )
                hb_stream_delete_ts_entry(stream, i);
        }
    }
    return 0;
}