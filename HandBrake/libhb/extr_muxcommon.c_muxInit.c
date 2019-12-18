#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  list_work; int /*<<< orphan*/  track; TYPE_7__* mux; TYPE_8__* job; } ;
typedef  TYPE_4__ hb_work_private_t ;
struct TYPE_25__ {int /*<<< orphan*/  name; int /*<<< orphan*/  thread; int /*<<< orphan*/  done; int /*<<< orphan*/  fifo_in; TYPE_4__* private_data; } ;
typedef  TYPE_5__ hb_work_object_t ;
struct TYPE_23__ {scalar_t__ dest; } ;
struct TYPE_26__ {int /*<<< orphan*/  mux_data; int /*<<< orphan*/  fifo_out; TYPE_3__ config; } ;
typedef  TYPE_6__ hb_subtitle_t ;
struct TYPE_27__ {int interleave; int pts; int /*<<< orphan*/  ntracks; TYPE_10__* m; int /*<<< orphan*/  mutex; void* allEof; void* allRdy; void* eof; void* rdy; } ;
typedef  TYPE_7__ hb_mux_t ;
struct TYPE_21__ {int num; scalar_t__ den; } ;
struct TYPE_28__ {scalar_t__ pass_id; int mux; int* die; int /*<<< orphan*/  h; int /*<<< orphan*/  list_subtitle; int /*<<< orphan*/  list_audio; int /*<<< orphan*/  mux_data; int /*<<< orphan*/  fifo_mpeg4; TYPE_1__ vrate; int /*<<< orphan*/ * done_error; } ;
typedef  TYPE_8__ hb_job_t ;
struct TYPE_22__ {int /*<<< orphan*/  mux_data; int /*<<< orphan*/  fifo_out; } ;
struct TYPE_29__ {TYPE_2__ priv; } ;
typedef  TYPE_9__ hb_audio_t ;
struct TYPE_20__ {int /*<<< orphan*/  (* init ) (TYPE_10__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HB_ERROR_INIT ; 
 int /*<<< orphan*/  HB_LOW_PRIORITY ; 
#define  HB_MUX_AV_MKV 130 
#define  HB_MUX_AV_MP4 129 
#define  HB_MUX_AV_WEBM 128 
 scalar_t__ HB_PASS_ENCODE ; 
 scalar_t__ HB_PASS_ENCODE_2ND ; 
 scalar_t__ PASSTHRUSUB ; 
 int /*<<< orphan*/  WORK_MUX ; 
 int /*<<< orphan*/  add_mux_track (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 
 void* hb_bitvec_new (int) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 TYPE_5__* hb_get_work (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_init () ; 
 void* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_lock_init () ; 
 TYPE_10__* hb_mux_avformat_init (TYPE_8__*) ; 
 int /*<<< orphan*/  hb_thread_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_work_loop ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*) ; 

__attribute__((used)) static int muxInit( hb_work_object_t * muxer, hb_job_t * job )
{
    muxer->private_data = calloc( sizeof( hb_work_private_t ), 1 );
    hb_work_private_t * pv = muxer->private_data;

    hb_mux_t         * mux = calloc( sizeof( hb_mux_t ), 1 );
    int                i;
    hb_work_object_t * w;

    /* Get a real muxer */
    if( job->pass_id == HB_PASS_ENCODE || job->pass_id == HB_PASS_ENCODE_2ND )
    {
        switch( job->mux )
        {
            case HB_MUX_AV_MP4:
            case HB_MUX_AV_MKV:
            case HB_MUX_AV_WEBM:
                mux->m = hb_mux_avformat_init( job );
                break;
            default:
                hb_error( "No muxer selected, exiting" );
                free(mux);
                *job->done_error = HB_ERROR_INIT;
                *job->die = 1;
                return -1;
        }
    }

    pv->list_work = hb_list_init();

    // The bit vectors must be allocated before hb_thread_init for the
    // audio and subtitle muxer jobs below.
    int bit_vec_size = 1 + hb_list_count(job->list_audio) +
                           hb_list_count(job->list_subtitle);
    mux->rdy = hb_bitvec_new(bit_vec_size);
    mux->eof = hb_bitvec_new(bit_vec_size);
    mux->allRdy = hb_bitvec_new(bit_vec_size);
    mux->allEof = hb_bitvec_new(bit_vec_size);

    mux->mutex = hb_lock_init();

    // set up to interleave track data in blocks of 1 video frame time.
    // (the best case for buffering and playout latency). The container-
    // specific muxers can reblock this into bigger chunks if necessary.
    mux->interleave = 90000. * (double)job->vrate.den / job->vrate.num;
    mux->pts = mux->interleave;

    if( job->pass_id == HB_PASS_ENCODE || job->pass_id == HB_PASS_ENCODE_2ND )
    {
        /* Create file, write headers */
        if( mux->m )
        {
            mux->m->init( mux->m );
        }
    }

    /* Initialize the work objects that will receive fifo data */
    pv->job = job;
    pv->mux = mux;
    pv->track = mux->ntracks;
    muxer->fifo_in = job->fifo_mpeg4;
    add_mux_track( mux, job->mux_data, 1 );

    for (i = 0; i < hb_list_count(job->list_audio); i++)
    {
        hb_audio_t  *audio = hb_list_item( job->list_audio, i );

        w = hb_get_work(job->h, WORK_MUX);
        w->private_data = calloc(sizeof(hb_work_private_t), 1);
        w->private_data->job = job;
        w->private_data->mux = mux;
        w->private_data->track = mux->ntracks;
        w->fifo_in = audio->priv.fifo_out;
        add_mux_track(mux, audio->priv.mux_data, 1);
        hb_list_add(pv->list_work, w);
    }

    for (i = 0; i < hb_list_count(job->list_subtitle); i++)
    {
        hb_subtitle_t  *subtitle = hb_list_item( job->list_subtitle, i );

        if (subtitle->config.dest != PASSTHRUSUB)
            continue;

        w = hb_get_work(job->h, WORK_MUX);
        w->private_data = calloc(sizeof(hb_work_private_t), 1);
        w->private_data->job = job;
        w->private_data->mux = mux;
        w->private_data->track = mux->ntracks;
        w->fifo_in = subtitle->fifo_out;
        add_mux_track(mux, subtitle->mux_data, 0);
        hb_list_add(pv->list_work, w);
    }

    /* Launch processing threads */
    for (i = 0; i < hb_list_count(pv->list_work); i++)
    {
        w = hb_list_item(pv->list_work, i);
        w->done = muxer->done;
        w->thread = hb_thread_init(w->name, hb_work_loop, w, HB_LOW_PRIORITY);
    }
    return 0;
}