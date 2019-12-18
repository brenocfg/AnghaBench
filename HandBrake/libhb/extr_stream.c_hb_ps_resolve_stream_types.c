#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int count; TYPE_4__* list; } ;
struct TYPE_18__ {TYPE_2__ pes; scalar_t__ need_keyframe; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_19__ {int stream_type; scalar_t__ stream_kind; scalar_t__ probe_next_size; TYPE_5__* probe_buf; int /*<<< orphan*/  stream_id_ext; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  codec_name; int /*<<< orphan*/  codec_param; int /*<<< orphan*/  codec; } ;
typedef  TYPE_4__ hb_pes_stream_t ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;
struct TYPE_20__ {TYPE_1__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_21__ {int /*<<< orphan*/  codec_param; int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 scalar_t__ A ; 
 void* N ; 
 scalar_t__ S ; 
 scalar_t__ U ; 
 scalar_t__ V ; 
 int do_probe (TYPE_3__*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_5__**) ; 
 int /*<<< orphan*/  hb_log (char*,int,char*,...) ; 
 TYPE_5__* hb_ps_stream_decode (TYPE_3__*) ; 
 int /*<<< orphan*/  hb_stream_seek (TYPE_3__*,double) ; 
 int index_of_id (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* st2codec ; 

__attribute__((used)) static void hb_ps_resolve_stream_types(hb_stream_t *stream)
{
    int ii, probe = 0;

    for ( ii = 0; ii < stream->pes.count; ii++ )
    {
        int stype = stream->pes.list[ii].stream_type;

        // stype == 0 indicates a type not in st2codec table
        if ( stype != 0 &&
             ( stream->pes.list[ii].stream_kind == A ||
               stream->pes.list[ii].stream_kind == S ||
               stream->pes.list[ii].stream_kind == V ) )
        {
            stream->pes.list[ii].codec = st2codec[stype].codec;
            stream->pes.list[ii].codec_param = st2codec[stype].codec_param;
            continue;
        }

        if ( stream->pes.list[ii].stream_kind == U )
        {
            probe++;
        }
    }

    // Probe remaining unknown streams for stream types
    hb_stream_seek( stream, 0.0 );
    stream->need_keyframe = 0;

    hb_buffer_t *buf;

    if ( probe )
        hb_log("Probing %d unknown stream%s", probe, probe > 1 ? "s" : "" );

    while ( probe && ( buf = hb_ps_stream_decode( stream ) ) != NULL )
    {
        int idx, result;
        idx = index_of_id( stream, buf->s.id );

        if (idx < 0 || stream->pes.list[idx].stream_kind != U )
        {
            hb_buffer_close(&buf);
            continue;
        }

        hb_pes_stream_t *pes = &stream->pes.list[idx];

        result = do_probe(stream, pes, buf);
        if (result < 0)
        {
            hb_log("    Probe: Unsupported stream %s. stream id 0x%x-0x%x",
                    pes->codec_name, pes->stream_id, pes->stream_id_ext);
            pes->stream_kind = N;
            probe--;
        }
        else if (result && pes->stream_kind != U)
        {
            hb_log("    Probe: Found stream %s. stream id 0x%x-0x%x",
                    pes->codec_name, pes->stream_id, pes->stream_id_ext);
            probe--;
        }
        hb_buffer_close(&buf);
    }
    // Clean up any probe buffers and set all remaining unknown
    // streams to 'kind' N
    for ( ii = 0; ii < stream->pes.count; ii++ )
    {
        if ( stream->pes.list[ii].stream_kind == U )
            stream->pes.list[ii].stream_kind = N;
        hb_buffer_close( &stream->pes.list[ii].probe_buf );
        stream->pes.list[ii].probe_next_size = 0;
    }
}