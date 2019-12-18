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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* context; int /*<<< orphan*/  codec; scalar_t__ parser; scalar_t__ video_codec_opened; TYPE_1__* title; int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_10__ {int /*<<< orphan*/  codec_param; TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
struct TYPE_11__ {int /*<<< orphan*/ * codec; } ;
struct TYPE_8__ {int /*<<< orphan*/ * opaque_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_parser_close (scalar_t__) ; 
 scalar_t__ av_parser_init (int /*<<< orphan*/ ) ; 
 TYPE_4__* avcodec_alloc_context3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_flush_buffers (TYPE_4__*) ; 
 int /*<<< orphan*/  hb_avcodec_free_context (TYPE_4__**) ; 
 int /*<<< orphan*/  hb_buffer_list_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decavcodecvFlush( hb_work_object_t *w )
{
    hb_work_private_t *pv = w->private_data;

    if (pv->context != NULL && pv->context->codec != NULL)
    {
        hb_buffer_list_close(&pv->list);
        if ( pv->title->opaque_priv == NULL )
        {
            pv->video_codec_opened = 0;
            hb_avcodec_free_context(&pv->context);
            if ( pv->parser )
            {
                av_parser_close(pv->parser);
            }
            pv->parser = av_parser_init( w->codec_param );
            pv->context = avcodec_alloc_context3( pv->codec );
        }
        else
        {
            avcodec_flush_buffers( pv->context );
        }
    }
}