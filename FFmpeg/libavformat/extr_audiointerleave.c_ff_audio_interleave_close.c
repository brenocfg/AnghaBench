#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_8__ {TYPE_1__* codecpar; TYPE_2__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  fifo; } ;
struct TYPE_6__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ AudioInterleaveContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  av_fifo_freep (int /*<<< orphan*/ *) ; 

void ff_audio_interleave_close(AVFormatContext *s)
{
    int i;
    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        AudioInterleaveContext *aic = st->priv_data;

        if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
            av_fifo_freep(&aic->fifo);
    }
}