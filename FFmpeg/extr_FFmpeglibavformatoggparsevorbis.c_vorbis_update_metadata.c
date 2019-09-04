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
struct ogg_stream {int psize; scalar_t__ new_metadata_size; int /*<<< orphan*/  new_metadata; scalar_t__ pstart; scalar_t__ buf; } ;
struct ogg {struct ogg_stream* streams; } ;
struct TYPE_7__ {TYPE_1__** streams; struct ogg* priv_data; } ;
struct TYPE_6__ {scalar_t__ metadata; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_malloc (int) ; 
 int /*<<< orphan*/  av_packet_pack_dictionary (scalar_t__,scalar_t__*) ; 
 int ff_vorbis_stream_comment (TYPE_2__*,TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static int vorbis_update_metadata(AVFormatContext *s, int idx)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    AVStream *st = s->streams[idx];
    int ret;

    if (os->psize <= 8)
        return 0;

    /* New metadata packet; release old data. */
    av_dict_free(&st->metadata);
    ret = ff_vorbis_stream_comment(s, st, os->buf + os->pstart + 7,
                                   os->psize - 8);
    if (ret < 0)
        return ret;

    /* Update the metadata if possible. */
    av_freep(&os->new_metadata);
    if (st->metadata) {
        os->new_metadata = av_packet_pack_dictionary(st->metadata, &os->new_metadata_size);
    /* Send an empty dictionary to indicate that metadata has been cleared. */
    } else {
        os->new_metadata = av_malloc(1);
        os->new_metadata_size = 0;
    }

    return ret;
}