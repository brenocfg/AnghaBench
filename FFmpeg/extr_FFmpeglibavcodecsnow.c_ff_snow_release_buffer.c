#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__* data; } ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_7__ {int max_ref_frames; int /*<<< orphan*/ **** halfpel_plane; TYPE_1__* current_picture; TYPE_5__** last_picture; } ;
struct TYPE_6__ {int* linesize; } ;
typedef  TYPE_2__ SnowContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int EDGE_WIDTH ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_5__*) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 

void ff_snow_release_buffer(AVCodecContext *avctx)
{
    SnowContext *s = avctx->priv_data;
    int i;

    if(s->last_picture[s->max_ref_frames-1]->data[0]){
        av_frame_unref(s->last_picture[s->max_ref_frames-1]);
        for(i=0; i<9; i++)
            if(s->halfpel_plane[s->max_ref_frames-1][1+i/3][i%3]) {
                av_free(s->halfpel_plane[s->max_ref_frames-1][1+i/3][i%3] - EDGE_WIDTH*(1+s->current_picture->linesize[i%3]));
                s->halfpel_plane[s->max_ref_frames-1][1+i/3][i%3] = NULL;
            }
    }
}