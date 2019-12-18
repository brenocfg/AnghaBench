#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__** reordered_hash; int /*<<< orphan*/  resample; TYPE_3__* context; scalar_t__ parser; int /*<<< orphan*/  frame; int /*<<< orphan*/  decode_errors; int /*<<< orphan*/  nframes; scalar_t__ job; int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_10__ {TYPE_1__* codec; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int REORDERED_HASH_SZ ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_parser_close (scalar_t__) ; 
 int /*<<< orphan*/  close_video_filters (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hb_audio_resample_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_avcodec_free_context (TYPE_3__**) ; 
 int /*<<< orphan*/  hb_buffer_list_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_qsv_uninit_dec (TYPE_3__*) ; 

__attribute__((used)) static void closePrivData( hb_work_private_t ** ppv )
{
    hb_work_private_t * pv = *ppv;

    if ( pv )
    {
        hb_buffer_list_close(&pv->list);

        if ( pv->job && pv->context && pv->context->codec )
        {
            hb_log( "%s-decoder done: %u frames, %u decoder errors",
                    pv->context->codec->name, pv->nframes, pv->decode_errors);
        }
        av_frame_free(&pv->frame);
        close_video_filters(pv);
        if ( pv->parser )
        {
            av_parser_close(pv->parser);
        }
        if ( pv->context && pv->context->codec )
        {
#if HB_PROJECT_FEATURE_QSV
            /*
             * FIXME: knowingly leaked.
             *
             * If we're using our FFmpeg QSV wrapper, qsv_decode_end() will call
             * MFXClose() on the QSV session. Even if decoding is complete, we
             * still need that session for QSV filtering and/or encoding, so we
             * we can't close the context here until we implement a proper fix.
             *
             * Interestingly, this may cause crashes even when QSV-accelerated
             * decoding and encoding sessions are independent (e.g. decoding via
             * libavcodec, but encoding using libhb, without us requesting any
             * form of communication between the two libmfx sessions).
             */
            //if (!(pv->qsv.decode && pv->job != NULL && (pv->job->vcodec & HB_VCODEC_QSV_MASK)))
            hb_qsv_uninit_dec(pv->context);
#endif
            {
                hb_avcodec_free_context(&pv->context);
            }
        }
        if ( pv->context )
        {
            hb_avcodec_free_context(&pv->context);
        }
        hb_audio_resample_free(pv->resample);

        int ii;
        for (ii = 0; ii < REORDERED_HASH_SZ; ii++)
        {
            free(pv->reordered_hash[ii]);
        }
        free(pv);
    }
    *ppv = NULL;
}