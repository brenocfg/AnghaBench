#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x264_picture_t ;
typedef  int /*<<< orphan*/  x264_nal_t ;
struct TYPE_18__ {int /*<<< orphan*/  x264; TYPE_2__* api; } ;
typedef  TYPE_3__ hb_work_private_t ;
struct TYPE_19__ {TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_work_object_t ;
struct TYPE_16__ {int flags; } ;
struct TYPE_20__ {TYPE_1__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* encoder_encode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* encoder_delayed_frames ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_5__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 TYPE_5__* nal_encode (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* x264_encode (TYPE_4__*,TYPE_5__*) ; 

int encx264Work( hb_work_object_t * w, hb_buffer_t ** buf_in,
                  hb_buffer_t ** buf_out )
{
    hb_work_private_t *pv = w->private_data;
    hb_buffer_t *in = *buf_in;

    *buf_out = NULL;

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        // EOF on input. Flush any frames still in the decoder then
        // send the eof downstream to tell the muxer we're done.
        x264_picture_t pic_out;
        int i_nal;
        x264_nal_t *nal;
        hb_buffer_list_t list;

        hb_buffer_list_clear(&list);

        // flush delayed frames
        while ( pv->api->encoder_delayed_frames( pv->x264 ) )
        {
            pv->api->encoder_encode( pv->x264, &nal, &i_nal, NULL, &pic_out );
            if ( i_nal == 0 )
                continue;
            if ( i_nal < 0 )
                break;

            hb_buffer_t *buf = nal_encode( w, &pic_out, i_nal, nal );
            hb_buffer_list_append(&list, buf);
        }
        // add the EOF to the end of the chain
        hb_buffer_list_append(&list, in);

        *buf_out = hb_buffer_list_clear(&list);
        *buf_in = NULL;
        return HB_WORK_DONE;
    }

    // Not EOF - encode the packet & wrap it in a NAL
    *buf_out = x264_encode( w, in );
    return HB_WORK_OK;
}