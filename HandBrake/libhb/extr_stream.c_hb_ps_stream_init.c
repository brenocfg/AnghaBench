#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int alloc; int count; TYPE_4__* list; } ;
struct TYPE_10__ {TYPE_1__ pes; scalar_t__ scan; } ;
typedef  TYPE_2__ hb_stream_t ;
struct TYPE_11__ {int stream_id; int next; scalar_t__ stream_kind; int /*<<< orphan*/  stream_type; int /*<<< orphan*/  stream_id_ext; } ;

/* Variables and functions */
 scalar_t__ A ; 
 scalar_t__ N ; 
 scalar_t__ S ; 
 scalar_t__ V ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  hb_ps_resolve_stream_types (TYPE_2__*) ; 
 int /*<<< orphan*/  hb_ps_stream_find_streams (TYPE_2__*) ; 
 int /*<<< orphan*/  hb_stream_delete_ps_entry (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stream_type_name2 (TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static void hb_ps_stream_init(hb_stream_t *stream)
{
    int i;

    if ( stream->pes.list )
    {
        for (i=0; i < stream->pes.alloc; i++)
        {
            stream->pes.list[i].stream_id = -1;
            stream->pes.list[i].next = -1;
        }
    }
    stream->pes.count = 0;

    // Find the audio and video pids in the stream
    hb_ps_stream_find_streams(stream);
    hb_ps_resolve_stream_types(stream);

    if( stream->scan )
    {
        hb_log("Found the following streams");
        hb_log("    Video Streams : ");
        for (i=0; i < stream->pes.count; i++)
        {
            if ( stream->pes.list[i].stream_kind == V )
            {
                hb_log( "      0x%x-0x%x type %s (0x%x)",
                        stream->pes.list[i].stream_id,
                        stream->pes.list[i].stream_id_ext,
                        stream_type_name2(stream,
                                         &stream->pes.list[i]),
                        stream->pes.list[i].stream_type);
            }
        }
        hb_log("    Audio Streams : ");
        for (i = 0; i < stream->pes.count; i++)
        {
            if ( stream->pes.list[i].stream_kind == A )
            {
                hb_log( "      0x%x-0x%x type %s (0x%x)",
                        stream->pes.list[i].stream_id,
                        stream->pes.list[i].stream_id_ext,
                        stream_type_name2(stream,
                                         &stream->pes.list[i]),
                        stream->pes.list[i].stream_type );
            }
        }
        hb_log("    Subtitle Streams : ");
        for (i = 0; i < stream->pes.count; i++)
        {
            if ( stream->pes.list[i].stream_kind == S )
            {
                hb_log( "      0x%x-0x%x type %s (0x%x)",
                        stream->pes.list[i].stream_id,
                        stream->pes.list[i].stream_id_ext,
                        stream_type_name2(stream,
                                         &stream->pes.list[i]),
                        stream->pes.list[i].stream_type );
            }
        }
        hb_log("    Other Streams : ");
        for (i = 0; i < stream->pes.count; i++)
        {
            if ( stream->pes.list[i].stream_kind == N )
            {
                hb_log( "      0x%x-0x%x type %s (0x%x)",
                        stream->pes.list[i].stream_id,
                        stream->pes.list[i].stream_id_ext,
                        stream_type_name2(stream,
                                         &stream->pes.list[i]),
                        stream->pes.list[i].stream_type );
                hb_stream_delete_ps_entry(stream, i);
            }
        }
    }
    else
    {
        for (i = 0; i < stream->pes.count; i++)
        {
            if ( stream->pes.list[i].stream_kind == N )
                hb_stream_delete_ps_entry(stream, i);
        }
    }
}