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
struct TYPE_9__ {TYPE_3__* avf; } ;
typedef  TYPE_2__ WebMChunkContext ;
struct TYPE_10__ {scalar_t__ nb_streams; int /*<<< orphan*/ * streams; TYPE_1__* oformat; TYPE_2__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* write_trailer ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avformat_free_context (TYPE_3__*) ; 
 int /*<<< orphan*/  chunk_end (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int webm_chunk_write_trailer(AVFormatContext *s)
{
    WebMChunkContext *wc = s->priv_data;
    AVFormatContext *oc = wc->avf;
    oc->oformat->write_trailer(oc);
    chunk_end(s);
    oc->streams = NULL;
    oc->nb_streams = 0;
    avformat_free_context(oc);
    return 0;
}