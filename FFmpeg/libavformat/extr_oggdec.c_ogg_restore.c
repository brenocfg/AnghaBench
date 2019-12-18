#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ogg_stream {int /*<<< orphan*/  new_metadata; int /*<<< orphan*/  buf; } ;
struct ogg_state {int nstreams; TYPE_3__* streams; int /*<<< orphan*/  curidx; int /*<<< orphan*/  pos; struct ogg_state* next; } ;
struct ogg {int nstreams; int page_pos; struct ogg_stream* streams; int /*<<< orphan*/  curidx; struct ogg_state* state; } ;
struct TYPE_6__ {int /*<<< orphan*/  private; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pb; struct ogg* priv_data; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_free (struct ogg_state*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int av_reallocp_array (struct ogg_stream**,int,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_stream (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (struct ogg_stream*,TYPE_3__*,int) ; 

__attribute__((used)) static int ogg_restore(AVFormatContext *s)
{
    struct ogg *ogg = s->priv_data;
    AVIOContext *bc = s->pb;
    struct ogg_state *ost = ogg->state;
    int i, err;

    if (!ost)
        return 0;

    ogg->state = ost->next;

        for (i = 0; i < ogg->nstreams; i++) {
            struct ogg_stream *stream = &ogg->streams[i];
            av_freep(&stream->buf);
            av_freep(&stream->new_metadata);

            if (i >= ost->nstreams || !ost->streams[i].private) {
                free_stream(s, i);
            }
        }

        avio_seek(bc, ost->pos, SEEK_SET);
        ogg->page_pos = -1;
        ogg->curidx   = ost->curidx;
        ogg->nstreams = ost->nstreams;
        if ((err = av_reallocp_array(&ogg->streams, ogg->nstreams,
                                     sizeof(*ogg->streams))) < 0) {
            ogg->nstreams = 0;
            return err;
        } else
            memcpy(ogg->streams, ost->streams,
                   ost->nstreams * sizeof(*ogg->streams));

    av_free(ost);

    return 0;
}