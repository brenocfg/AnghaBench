#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct SAPState {int* ann; scalar_t__ ann_fd; int /*<<< orphan*/  ann_size; scalar_t__ last_time; } ;
struct TYPE_7__ {int nb_streams; TYPE_1__** streams; int /*<<< orphan*/  pb; struct SAPState* priv_data; } ;
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_write_trailer (TYPE_2__*) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_closep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_network_close () ; 
 int /*<<< orphan*/  ffurl_close (scalar_t__) ; 
 int /*<<< orphan*/  ffurl_write (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sap_write_close(AVFormatContext *s)
{
    struct SAPState *sap = s->priv_data;
    int i;

    for (i = 0; i < s->nb_streams; i++) {
        AVFormatContext *rtpctx = s->streams[i]->priv_data;
        if (!rtpctx)
            continue;
        av_write_trailer(rtpctx);
        avio_closep(&rtpctx->pb);
        avformat_free_context(rtpctx);
        s->streams[i]->priv_data = NULL;
    }

    if (sap->last_time && sap->ann && sap->ann_fd) {
        sap->ann[0] |= 4; /* Session deletion*/
        ffurl_write(sap->ann_fd, sap->ann, sap->ann_size);
    }

    av_freep(&sap->ann);
    if (sap->ann_fd)
        ffurl_close(sap->ann_fd);
    ff_network_close();
    return 0;
}