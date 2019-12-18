#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int discard_subtitle; TYPE_6__* context; int /*<<< orphan*/ * job; int /*<<< orphan*/  last_pts; scalar_t__ seen_forced_sub; int /*<<< orphan*/  list_pass; int /*<<< orphan*/  list; } ;
typedef  TYPE_4__ hb_work_private_t ;
struct TYPE_15__ {TYPE_3__* subtitle; TYPE_4__* private_data; } ;
typedef  TYPE_5__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_job_t ;
struct TYPE_11__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_16__ {TYPE_1__ pkt_timebase; int /*<<< orphan*/ * codec; } ;
struct TYPE_12__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_13__ {TYPE_2__ timebase; } ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_6__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_HDMV_PGS_SUBTITLE ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_6__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 TYPE_4__* calloc (int,int) ; 
 scalar_t__ hb_avcodec_open (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*) ; 

__attribute__((used)) static int decsubInit( hb_work_object_t * w, hb_job_t * job )
{
    AVCodec *codec = avcodec_find_decoder( AV_CODEC_ID_HDMV_PGS_SUBTITLE );
    AVCodecContext *context = avcodec_alloc_context3( codec );
    context->codec = codec;

    hb_work_private_t * pv;
    pv = calloc( 1, sizeof( hb_work_private_t ) );
    w->private_data = pv;

    hb_buffer_list_clear(&pv->list);
    hb_buffer_list_clear(&pv->list_pass);
    pv->discard_subtitle      = 1;
    pv->seen_forced_sub       = 0;
    pv->last_pts              = AV_NOPTS_VALUE;
    pv->context               = context;
    context->pkt_timebase.num = w->subtitle->timebase.num;
    context->pkt_timebase.den = w->subtitle->timebase.den;
    pv->job                   = job;

    // Set decoder opts...
    AVDictionary * av_opts = NULL;
    // e.g. av_dict_set( &av_opts, "refcounted_frames", "1", 0 );

    if (hb_avcodec_open(pv->context, codec, &av_opts, 0))
    {
        av_dict_free( &av_opts );
        hb_log("decsubInit: avcodec_open failed");
        return 1;
    }
    av_dict_free( &av_opts );


    return 0;
}