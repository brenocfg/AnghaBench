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
struct TYPE_9__ {int /*<<< orphan*/  dec_ctx; TYPE_2__* st; } ;
struct TYPE_8__ {int nb_streams; int /*<<< orphan*/  fmt_ctx; TYPE_5__* streams; } ;
struct TYPE_7__ {TYPE_1__* codecpar; } ;
struct TYPE_6__ {scalar_t__ codec_id; } ;
typedef  TYPE_3__ InputFile ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  av_freep (TYPE_5__**) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_input_file(InputFile *ifile)
{
    int i;

    /* close decoder for each stream */
    for (i = 0; i < ifile->nb_streams; i++)
        if (ifile->streams[i].st->codecpar->codec_id != AV_CODEC_ID_NONE)
            avcodec_free_context(&ifile->streams[i].dec_ctx);

    av_freep(&ifile->streams);
    ifile->nb_streams = 0;

    avformat_close_input(&ifile->fmt_ctx);
}