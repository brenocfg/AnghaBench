#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct pullup_frame {int length; TYPE_4__* buffer; } ;
struct pullup_context {int parity; } ;
struct pullup_buffer {int /*<<< orphan*/ * size; int /*<<< orphan*/ * planes; } ;
struct TYPE_14__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_18__ {TYPE_2__ output; scalar_t__ pullup_fakecount; struct pullup_context* pullup_ctx; } ;
typedef  TYPE_6__ hb_filter_private_t ;
struct TYPE_19__ {TYPE_6__* private_data; } ;
typedef  TYPE_7__ hb_filter_object_t ;
struct TYPE_17__ {int flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_20__ {TYPE_5__ s; TYPE_3__* plane; TYPE_1__ f; } ;
typedef  TYPE_8__ hb_buffer_t ;
struct TYPE_16__ {int /*<<< orphan*/ * size; int /*<<< orphan*/ * planes; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_FAILED ; 
 int HB_FILTER_OK ; 
 int PIC_FLAG_REPEAT_FIRST_FIELD ; 
 int PIC_FLAG_TOP_FIELD_FIRST ; 
 TYPE_8__* hb_frame_buffer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pullup_buffer* pullup_get_buffer (struct pullup_context*,int) ; 
 struct pullup_frame* pullup_get_frame (struct pullup_context*) ; 
 int /*<<< orphan*/  pullup_pack_frame (struct pullup_context*,struct pullup_frame*) ; 
 int /*<<< orphan*/  pullup_release_buffer (struct pullup_buffer*,int) ; 
 int /*<<< orphan*/  pullup_release_frame (struct pullup_frame*) ; 
 int /*<<< orphan*/  pullup_submit_field (struct pullup_context*,struct pullup_buffer*,int) ; 

__attribute__((used)) static int hb_detelecine_work( hb_filter_object_t * filter,
                               hb_buffer_t ** buf_in,
                               hb_buffer_t ** buf_out )
{
    hb_filter_private_t * pv = filter->private_data;
    hb_buffer_t * in = *buf_in, * out;

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        *buf_out = in;
        *buf_in = NULL;
        return HB_FILTER_DONE;
    }

    struct pullup_context * ctx = pv->pullup_ctx;
    struct pullup_buffer  * buf;
    struct pullup_frame   * frame;

    buf = pullup_get_buffer( ctx, 2 );
    if( !buf )
    {
        frame = pullup_get_frame( ctx );
        pullup_release_frame( frame );
        hb_log( "Could not get buffer from pullup!" );
        return HB_FILTER_FAILED;
    }

    /* Copy input buffer into pullup buffer */
    memcpy( buf->planes[0], in->plane[0].data, buf->size[0] );
    memcpy( buf->planes[1], in->plane[1].data, buf->size[1] );
    memcpy( buf->planes[2], in->plane[2].data, buf->size[2] );

    /* Submit buffer fields based on buffer flags.
       Detelecine assumes BFF when the TFF flag isn't present. */
    int parity = 1;
    if( in->s.flags & PIC_FLAG_TOP_FIELD_FIRST )
    {
        /* Source signals TFF */
        parity = 0;
    }
    else if( ctx->parity == 0 )
    {
        /* Many non-MPEG-2 sources lack parity flags even though
           they are TFF, so this allow users to override. */
        parity = 0;
    }
    if( ctx->parity == 1 )
    {
        /* Override autodetected parity with BFF */
        parity = 1;
    }
    pullup_submit_field( ctx, buf, parity );
    pullup_submit_field( ctx, buf, parity^1 );
    if( in->s.flags & PIC_FLAG_REPEAT_FIRST_FIELD )
    {
        pullup_submit_field( ctx, buf, parity );
    }
    pullup_release_buffer( buf, 2 );

    /* Get frame and check if pullup is ready */
    frame = pullup_get_frame( ctx );
    if( !frame )
    {
        if( pv->pullup_fakecount )
        {
            pv->pullup_fakecount--;

            *buf_in = NULL;
            *buf_out = in;

            goto output_frame;
        }
        else
        {
            goto discard_frame;
        }
    }

    /* Check to see if frame should be dropped */
    if( frame->length < 2 )
    {
        pullup_release_frame( frame );
        frame = pullup_get_frame( ctx );

        if (!frame)
        {
            goto discard_frame;
        }
        if( frame->length < 2 )
        {
            pullup_release_frame( frame );

            if( !(in->s.flags & PIC_FLAG_REPEAT_FIRST_FIELD) )
            {
                goto discard_frame;
            }

            frame = pullup_get_frame( ctx );

            if( !frame )
            {
                goto discard_frame;
            }
            if( frame->length < 2 )
            {
                pullup_release_frame( frame );
                goto discard_frame;
            }
        }
    }

    /* Check to see if frame buffer is ready for export */
    if( !frame->buffer )
    {
        pullup_pack_frame( ctx, frame );
    }

    out = hb_frame_buffer_init(pv->output.pix_fmt, in->f.width, in->f.height);
    out->f.color_prim     = pv->output.color_prim;
    out->f.color_transfer = pv->output.color_transfer;
    out->f.color_matrix   = pv->output.color_matrix;
    out->f.color_range    = pv->output.color_range ;

    /* Copy pullup frame buffer into output buffer */
    memcpy( out->plane[0].data, frame->buffer->planes[0], frame->buffer->size[0] );
    memcpy( out->plane[1].data, frame->buffer->planes[1], frame->buffer->size[1] );
    memcpy( out->plane[2].data, frame->buffer->planes[2], frame->buffer->size[2] );

    pullup_release_frame( frame );

    out->s = in->s;
    *buf_out = out;

output_frame:

    return HB_FILTER_OK;

/* This and all discard_frame calls shown above are
   the result of me restoring the functionality in
   pullup that huevos_rancheros disabled because
   HB couldn't handle it.                           */
discard_frame:
    return HB_FILTER_OK;

}