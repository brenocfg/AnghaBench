#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int size_sub; int size_rle; int size_got; scalar_t__ pts; scalar_t__ pts_stop; int /*<<< orphan*/  scr_sequence; int /*<<< orphan*/  current_scr_sequence; TYPE_6__* buf; int /*<<< orphan*/  stream_id; } ;
typedef  TYPE_3__ hb_work_private_t ;
struct TYPE_16__ {TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_work_object_t ;
struct TYPE_14__ {int flags; scalar_t__ start; int /*<<< orphan*/  id; int /*<<< orphan*/  scr_sequence; } ;
struct TYPE_17__ {int* data; int size; TYPE_2__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_13__ {int /*<<< orphan*/  id; int /*<<< orphan*/  frametype; } ;
struct TYPE_18__ {int size; TYPE_1__ s; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 TYPE_5__* Decode (TYPE_4__*) ; 
 int HB_BUF_FLAG_EOF ; 
 int /*<<< orphan*/  HB_FRAME_SUBTITLE ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_6__**) ; 
 TYPE_6__* hb_buffer_init (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 

int decsubWork( hb_work_object_t * w, hb_buffer_t ** buf_in,
                hb_buffer_t ** buf_out )
{
    hb_work_private_t * pv = w->private_data;
    hb_buffer_t * in = *buf_in;
    int size_sub, size_rle;

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        /* EOF on input stream - send it downstream & say that we're done */
        *buf_out = in;
        *buf_in = NULL;
        return HB_WORK_DONE;
    }

    pv->stream_id = in->s.id;

    size_sub = ( in->data[0] << 8 ) | in->data[1];
    size_rle = ( in->data[2] << 8 ) | in->data[3];

    if( !pv->size_sub )
    {
        /* We are looking for the start of a new subtitle */
        if( size_sub && size_rle && size_sub > size_rle &&
            in->size <= size_sub )
        {
            /* Looks all right so far */
            pv->size_sub = size_sub;
            pv->size_rle = size_rle;

            pv->buf      = hb_buffer_init( 0xFFFF );
            memcpy( pv->buf->data, in->data, in->size );
            pv->buf->s.id = in->s.id;
            pv->buf->s.frametype = HB_FRAME_SUBTITLE;
            pv->size_got = in->size;
            if( in->s.start >= 0 )
            {
                pv->pts                  = in->s.start;
                pv->current_scr_sequence = in->s.scr_sequence;
            }
        }
    }
    else
    {
        /* We are waiting for the end of the current subtitle */
        if( in->size <= pv->size_sub - pv->size_got )
        {
            memcpy( pv->buf->data + pv->size_got, in->data, in->size );
            pv->buf->s.id = in->s.id;
            pv->size_got += in->size;
            if( in->s.start >= 0 )
            {
                pv->pts                  = in->s.start;
                pv->current_scr_sequence = in->s.scr_sequence;
            }
        }
        else
        {
            // bad size, must have lost sync
            // force re-sync
            if ( pv->buf != NULL )
                hb_buffer_close( &pv->buf );
            pv->size_sub = 0;
        }

    }

    *buf_out = NULL;

    if( pv->size_sub && pv->size_sub == pv->size_got )
    {
        pv->buf->size = pv->size_sub;

        /* We got a complete subtitle, decode it */
        *buf_out = Decode( w );

        if ( *buf_out != NULL )
            (*buf_out)->s.id = in->s.id;

        /* Wait for the next one */
        pv->size_sub = 0;
        pv->size_got = 0;
        pv->size_rle = 0;

        if ( pv->pts_stop != AV_NOPTS_VALUE )
        {
            // If we don't get a valid next timestamp, use the stop time
            // of the current sub as the start of the next.
            // This can happen if reader invalidates timestamps while
            // waiting for an audio to update the SCR.
            pv->pts                  = pv->pts_stop;
            pv->current_scr_sequence = pv->scr_sequence;
        }
    }

    return HB_WORK_OK;
}