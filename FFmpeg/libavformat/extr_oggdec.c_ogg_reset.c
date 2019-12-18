#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ogg_stream {int granule; int sync_pos; scalar_t__ new_metadata_size; int /*<<< orphan*/  new_metadata; scalar_t__ end_trimming; void* lastpts; scalar_t__ got_data; scalar_t__ incomplete; scalar_t__ segp; scalar_t__ nsegs; scalar_t__ page_pos; void* lastdts; scalar_t__ psize; scalar_t__ pstart; scalar_t__ bufpos; } ;
struct ogg {int nstreams; int page_pos; int curidx; struct ogg_stream* streams; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_1__* internal; int /*<<< orphan*/  pb; struct ogg* priv_data; } ;
struct TYPE_4__ {scalar_t__ data_offset; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ogg_reset(AVFormatContext *s)
{
    struct ogg *ogg = s->priv_data;
    int i;
    int64_t start_pos = avio_tell(s->pb);

    for (i = 0; i < ogg->nstreams; i++) {
        struct ogg_stream *os = ogg->streams + i;
        os->bufpos     = 0;
        os->pstart     = 0;
        os->psize      = 0;
        os->granule    = -1;
        os->lastpts    = AV_NOPTS_VALUE;
        os->lastdts    = AV_NOPTS_VALUE;
        os->sync_pos   = -1;
        os->page_pos   = 0;
        os->nsegs      = 0;
        os->segp       = 0;
        os->incomplete = 0;
        os->got_data = 0;
        if (start_pos <= s->internal->data_offset) {
            os->lastpts = 0;
        }
        os->end_trimming = 0;
        av_freep(&os->new_metadata);
        os->new_metadata_size = 0;
    }

    ogg->page_pos = -1;
    ogg->curidx = -1;

    return 0;
}