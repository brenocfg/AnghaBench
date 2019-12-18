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
struct TYPE_14__ {scalar_t__ status; int frame_go; int /*<<< orphan*/  frame_completed_lock; int /*<<< orphan*/  frame_completed; } ;
struct TYPE_16__ {TYPE_2__ post; } ;
typedef  TYPE_4__ hb_filter_private_t_qsv ;
struct TYPE_17__ {scalar_t__ status; scalar_t__ chapter_time; scalar_t__ (* work ) (TYPE_5__*,TYPE_6__**,TYPE_6__**) ;int /*<<< orphan*/  fifo_in; scalar_t__* done; int /*<<< orphan*/ * fifo_out; scalar_t__ chapter_val; } ;
typedef  TYPE_5__ hb_filter_object_t ;
struct TYPE_15__ {scalar_t__ start; scalar_t__ new_chap; } ;
struct TYPE_13__ {TYPE_4__* filter_details; } ;
struct TYPE_18__ {TYPE_3__ s; TYPE_1__ qsv_details; } ;
typedef  TYPE_6__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ HB_FILTER_DELAY ; 
 scalar_t__ HB_FILTER_DONE ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_6__**) ; 
 int /*<<< orphan*/  hb_cond_broadcast (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_fifo_full_wait (int /*<<< orphan*/ *) ; 
 TYPE_6__* hb_fifo_get_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_fifo_push (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_6__**,TYPE_6__**) ; 

__attribute__((used)) static void filter_loop( void * _f )
{
    hb_filter_object_t * f = _f;
    hb_buffer_t      * buf_in, * buf_out = NULL;

    while( !*f->done && f->status != HB_FILTER_DONE )
    {
        buf_in = hb_fifo_get_wait( f->fifo_in );
        if ( buf_in == NULL )
            continue;

        // Filters can drop buffers.  Remember chapter information
        // so that it can be propagated to the next buffer
        if ( buf_in->s.new_chap )
        {
            f->chapter_time = buf_in->s.start;
            f->chapter_val = buf_in->s.new_chap;
            // don't let 'filter_loop' put a chapter mark on the wrong buffer
            buf_in->s.new_chap = 0;
        }
        if ( *f->done )
        {
            if( buf_in )
            {
                hb_buffer_close( &buf_in );
            }
            break;
        }

        buf_out = NULL;

#if HB_PROJECT_FEATURE_QSV
        hb_buffer_t *last_buf_in = buf_in;
#endif

        f->status = f->work( f, &buf_in, &buf_out );

#if HB_PROJECT_FEATURE_QSV
        if (f->status == HB_FILTER_DELAY &&
            last_buf_in->qsv_details.filter_details != NULL && buf_out == NULL)
        {
            hb_filter_private_t_qsv *qsv_user = buf_in ? buf_in->qsv_details.filter_details : last_buf_in->qsv_details.filter_details ;
            qsv_user->post.status = f->status;

            hb_lock(qsv_user->post.frame_completed_lock);
            qsv_user->post.frame_go = 1;
            hb_cond_broadcast(qsv_user->post.frame_completed);
            hb_unlock(qsv_user->post.frame_completed_lock);

        }
#endif
        if ( buf_out && f->chapter_val && f->chapter_time <= buf_out->s.start )
        {
            buf_out->s.new_chap = f->chapter_val;
            f->chapter_val = 0;
        }

        if( buf_in )
        {
            hb_buffer_close( &buf_in );
        }
        if ( buf_out && f->fifo_out == NULL )
        {
            hb_buffer_close( &buf_out );
        }
        if( buf_out )
        {
            while ( !*f->done )
            {
                if ( hb_fifo_full_wait( f->fifo_out ) )
                {
                    hb_fifo_push( f->fifo_out, buf_out );
                    buf_out = NULL;
                    break;
                }
            }
        }
    }
    if ( buf_out )
    {
        hb_buffer_close( &buf_out );
    }

    // Consume data in incoming fifo till job complete so that
    // residual data does not stall the pipeline
    while( !*f->done )
    {
        buf_in = hb_fifo_get_wait( f->fifo_in );
        if ( buf_in != NULL )
            hb_buffer_close( &buf_in );
    }
}