#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct TYPE_19__ {int found_scr; int /*<<< orphan*/  scr; TYPE_16__* list; } ;
struct TYPE_20__ {int ts_flags; int need_keyframe; TYPE_2__ pes; int /*<<< orphan*/  frames; int /*<<< orphan*/  errors; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_21__ {int stream_id; scalar_t__ header_len; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  stream_id_ext; int /*<<< orphan*/  bd_substream_id; int /*<<< orphan*/  scr; } ;
typedef  TYPE_4__ hb_pes_info_t ;
struct TYPE_18__ {scalar_t__ type; int /*<<< orphan*/  renderOffset; int /*<<< orphan*/  start; int /*<<< orphan*/  pcr; int /*<<< orphan*/  id; } ;
struct TYPE_22__ {scalar_t__ size; scalar_t__ data; TYPE_1__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_17__ {int stream_kind; } ;

/* Variables and functions */
#define  A 129 
 scalar_t__ AUDIO_BUF ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  HB_DVD_READ_BUFFER_SIZE ; 
 scalar_t__ OTHER_BUF ; 
 int TS_HAS_PCR ; 
#define  V 128 
 scalar_t__ VIDEO_BUF ; 
 int /*<<< orphan*/  get_id (TYPE_16__*) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_5__**) ; 
 TYPE_5__* hb_buffer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_parse_ps (TYPE_3__*,scalar_t__,scalar_t__,TYPE_4__*) ; 
 int hb_ps_read_packet (TYPE_3__*,TYPE_5__*) ; 
 int index_of_ps_stream (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isIframe (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static hb_buffer_t * hb_ps_stream_decode( hb_stream_t *stream )
{
    hb_pes_info_t pes_info;
    hb_buffer_t *buf  = hb_buffer_init(HB_DVD_READ_BUFFER_SIZE);

    while (1)
    {
        buf->size = 0;
        int len = hb_ps_read_packet( stream, buf );
        if ( len == 0 )
        {
            // End of file
            hb_buffer_close( &buf );
            return buf;
        }
        if ( !hb_parse_ps( stream, buf->data, buf->size, &pes_info ) )
        {
            ++stream->errors;
            continue;
        }
        // pack header
        if ( pes_info.stream_id == 0xba )
        {
            stream->pes.found_scr = 1;
            stream->ts_flags |= TS_HAS_PCR;
            stream->pes.scr = pes_info.scr;
            continue;
        }

        // If we don't have a SCR yet but the stream has SCRs just loop
        // so we don't process anything until we have a clock reference.
        if ( !stream->pes.found_scr && ( stream->ts_flags & TS_HAS_PCR ) )
        {
            continue;
        }

        // system header
        if ( pes_info.stream_id == 0xbb )
            continue;

        int idx;
        if ( pes_info.stream_id == 0xbd )
        {
            idx = index_of_ps_stream( stream, pes_info.stream_id,
                                      pes_info.bd_substream_id );
        }
        else
        {
            idx = index_of_ps_stream( stream, pes_info.stream_id,
                                      pes_info.stream_id_ext );
        }

        // Is this a stream carrying data that we care about?
        if ( idx < 0 )
            continue;

        switch (stream->pes.list[idx].stream_kind)
        {
            case A:
                buf->s.type = AUDIO_BUF;
                break;

            case V:
                buf->s.type = VIDEO_BUF;
                break;

            default:
                buf->s.type = OTHER_BUF;
                break;
        }

        if ( stream->need_keyframe )
        {
            // we're looking for the first video frame because we're
            // doing random access during 'scan'
            if ( buf->s.type != VIDEO_BUF ||
                 !isIframe( stream, buf->data, buf->size ) )
            {
                // not the video stream or didn't find an I frame
                // but we'll only wait 600 video frames for an I frame.
                if ( buf->s.type != VIDEO_BUF || ++stream->need_keyframe < 600 )
                {
                    continue;
                }
            }
            stream->need_keyframe = 0;
        }
        if ( buf->s.type == VIDEO_BUF )
            ++stream->frames;

        buf->s.id = get_id( &stream->pes.list[idx] );
        buf->s.pcr = stream->pes.scr;
        buf->s.start = pes_info.pts;
        buf->s.renderOffset = pes_info.dts;
        memmove( buf->data, buf->data + pes_info.header_len,
                 buf->size - pes_info.header_len );
        buf->size -= pes_info.header_len;
        if ( buf->size == 0 )
            continue;
        stream->pes.scr = AV_NOPTS_VALUE;
        return buf;
    }
}