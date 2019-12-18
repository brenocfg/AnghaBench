#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int video_id; int video_stream_type; int flags; int /*<<< orphan*/  list_subtitle; int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_5__ hb_title_t ;
struct TYPE_20__ {int id; int stream_type; } ;
typedef  TYPE_6__ hb_subtitle_t ;
struct TYPE_18__ {int count; TYPE_3__* list; int /*<<< orphan*/ * packet; } ;
struct TYPE_21__ {int packetsize; TYPE_4__ ts; int /*<<< orphan*/  hb_stream_type; int /*<<< orphan*/ * path; TYPE_5__* title; int /*<<< orphan*/ * file_handle; int /*<<< orphan*/ * h; } ;
typedef  TYPE_7__ hb_stream_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
struct TYPE_15__ {int substream_type; int stream_type; } ;
struct TYPE_16__ {TYPE_1__ in; } ;
struct TYPE_22__ {int id; TYPE_2__ config; } ;
typedef  TYPE_8__ hb_audio_t ;
struct TYPE_17__ {TYPE_10__* buf; } ;
struct TYPE_14__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int HBTF_SCAN_COMPLETE ; 
 int HB_SUBTITLE_EMBEDDED_CC_TAG ; 
 int /*<<< orphan*/  P ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  V ; 
 TYPE_7__* calloc (int,int) ; 
 TYPE_10__* hb_buffer_init (int) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 void* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  transport ; 
 int /*<<< orphan*/  update_ts_streams (TYPE_7__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

hb_stream_t * hb_bd_stream_open( hb_handle_t *h, hb_title_t *title )
{
    int ii;

    hb_stream_t *d = calloc( sizeof( hb_stream_t ), 1 );
    if ( d == NULL )
    {
        hb_error( "hb_bd_stream_open: can't allocate space for stream state" );
        return NULL;
    }

    d->h = h;
    d->file_handle = NULL;
    d->title = title;
    d->path = NULL;
    d->ts.packet = NULL;

    int pid = title->video_id;
    int stream_type = title->video_stream_type;
    update_ts_streams( d, pid, 0, stream_type, V, NULL );

    hb_audio_t * audio;
    for ( ii = 0; ( audio = hb_list_item( title->list_audio, ii ) ); ++ii )
    {
        int stream_id_ext = audio->config.in.substream_type;
        pid = audio->id & 0xFFFF;
        stream_type = audio->config.in.stream_type;

        update_ts_streams( d, pid, stream_id_ext, stream_type, A, NULL );
    }

    hb_subtitle_t * subtitle;
    for ( ii = 0; ( subtitle = hb_list_item( title->list_subtitle, ii ) ); ++ii )
    {
        // If the subtitle track is CC embedded in the video stream, then
        // it does not have an independent pid.  In this case, we assigned
        // the subtitle->id to HB_SUBTITLE_EMBEDDED_CC_TAG.
        if (subtitle->id != HB_SUBTITLE_EMBEDDED_CC_TAG)
        {
            pid = subtitle->id & 0xFFFF;
            stream_type = subtitle->stream_type;

            update_ts_streams( d, pid, 0, stream_type, S, NULL );
        }
    }

    // We don't need to wait for a PCR when scanning. In fact, it
    // trips us up on the first preview of every title since we would
    // have to read quite a lot of data before finding the PCR.
    if ( title->flags & HBTF_SCAN_COMPLETE )
    {
        /* BD has PCRs, but the BD index always points to a packet
         * after a PCR packet, so we will not see the initial PCR
         * after any seek.  So don't set the flag that causes us
         * to drop packets till we see a PCR. */
        //d->ts_flags = TS_HAS_RAP | TS_HAS_PCR;

        // BD PCR PID is specified to always be 0x1001
        update_ts_streams( d, 0x1001, 0, -1, P, NULL );
    }

    d->packetsize = 192;
    d->hb_stream_type = transport;

    for ( ii = 0; ii < d->ts.count; ii++ )
    {
        d->ts.list[ii].buf = hb_buffer_init(d->packetsize);
        d->ts.list[ii].buf->size = 0;
    }

    return d;
}