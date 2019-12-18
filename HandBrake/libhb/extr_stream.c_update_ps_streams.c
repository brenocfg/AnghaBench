#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ kind_t ;
struct TYPE_8__ {int count; TYPE_6__* list; } ;
struct TYPE_9__ {TYPE_1__ pes; } ;
typedef  TYPE_2__ hb_stream_t ;
typedef  int /*<<< orphan*/  hb_pes_stream_t ;
struct TYPE_11__ {int stream_id; int stream_id_ext; scalar_t__ stream_kind; int map_idx; int stream_type; } ;
struct TYPE_10__ {int kind; } ;

/* Variables and functions */
 scalar_t__ P ; 
 scalar_t__ U ; 
 scalar_t__ V ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_6__*,int) ; 
 int new_pes (TYPE_2__*) ; 
 TYPE_4__* st2codec ; 

__attribute__((used)) static int update_ps_streams( hb_stream_t * stream, int stream_id, int stream_id_ext, int stream_type, int in_kind )
{
    int ii;
    int same_stream = -1;
    kind_t kind = in_kind == -1 ? st2codec[stream_type].kind : in_kind;

    for ( ii = 0; ii < stream->pes.count; ii++ )
    {
        if ( stream->pes.list[ii].stream_id == stream_id )
            same_stream = ii;

        if ( stream->pes.list[ii].stream_id == stream_id &&
             stream->pes.list[ii].stream_id_ext == 0 &&
             stream->pes.list[ii].stream_kind == U )
        {
            // This is an unknown stream type that hasn't been
            // given a stream_id_ext.  So match only to stream_id
            //
            // is the stream_id_ext being updated?
            if ( stream_id_ext != 0 )
                break;

            // If stream is already in the list and the new 'kind' is
            // PCR, Unknown, or same as before, just return the index
            // to the entry found.
            if ( kind == P || kind == U || kind == stream->pes.list[ii].stream_kind )
                return ii;
            // Update stream_type and kind
            break;
        }
        if ( stream_id == stream->pes.list[ii].stream_id &&
             stream_id_ext == stream->pes.list[ii].stream_id_ext )
        {
            // If stream is already in the list and the new 'kind' is
            // PCR and the old 'kind' is unknown, set the new 'kind'
            if ( kind == P && stream->pes.list[ii].stream_kind == U )
                break;

            // If stream is already in the list and the new 'kind' is
            // PCR, Unknown, or same as before, just return the index
            // to the entry found.
            if ( kind == P || kind == U || kind == stream->pes.list[ii].stream_kind )
                return ii;
            // Replace unknown 'kind' with known 'kind'
            break;
        }
        // Resolve multiple videos
        if ( kind == V && stream->pes.list[ii].stream_kind == V )
        {
            if ( stream_id <= stream->pes.list[ii].stream_id &&
                 stream_id_ext <= stream->pes.list[ii].stream_id_ext )
            {
                // Assume primary video stream has the smallest stream id
                // and only use the primary. move the current item
                // to the end of the list.  we want to keep it for
                // debug and informational purposes.
                int jj = new_pes( stream );
                memcpy( &stream->pes.list[jj], &stream->pes.list[ii],
                        sizeof( hb_pes_stream_t ) );
                break;
            }
        }
    }

    if ( ii == stream->pes.count )
    {
        ii = new_pes( stream );
        if ( same_stream >= 0 )
        {
            memcpy( &stream->pes.list[ii], &stream->pes.list[same_stream],
                    sizeof( hb_pes_stream_t ) );
        }
        else
        {
            stream->pes.list[ii].map_idx = -1;
        }
    }

    stream->pes.list[ii].stream_id = stream_id;
    stream->pes.list[ii].stream_id_ext = stream_id_ext;
    stream->pes.list[ii].stream_type = stream_type;
    stream->pes.list[ii].stream_kind = kind;
    return ii;
}