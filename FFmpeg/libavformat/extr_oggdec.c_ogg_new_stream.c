#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ogg_stream {int header; int /*<<< orphan*/  buf; int /*<<< orphan*/  start_granule; scalar_t__ bufsize; int /*<<< orphan*/  serial; } ;
struct ogg {int nstreams; struct ogg_stream* streams; scalar_t__ state; } ;
struct TYPE_9__ {struct ogg* priv_data; } ;
struct TYPE_8__ {int id; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ DECODER_BUFFER_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  OGG_NOGRANULE_VALUE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_malloc (scalar_t__) ; 
 struct ogg_stream* av_realloc (struct ogg_stream*,size_t) ; 
 scalar_t__ av_size_mult (int,int,size_t*) ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  memset (struct ogg_stream*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ogg_new_stream(AVFormatContext *s, uint32_t serial)
{
    struct ogg *ogg = s->priv_data;
    int idx         = ogg->nstreams;
    AVStream *st;
    struct ogg_stream *os;
    size_t size;

    if (ogg->state) {
        av_log(s, AV_LOG_ERROR, "New streams are not supposed to be added "
               "in between Ogg context save/restore operations.\n");
        return AVERROR_BUG;
    }

    /* Allocate and init a new Ogg Stream */
    if (av_size_mult(ogg->nstreams + 1, sizeof(*ogg->streams), &size) < 0 ||
        !(os = av_realloc(ogg->streams, size)))
        return AVERROR(ENOMEM);
    ogg->streams = os;
    os           = ogg->streams + idx;
    memset(os, 0, sizeof(*os));
    os->serial        = serial;
    os->bufsize       = DECODER_BUFFER_SIZE;
    os->buf           = av_malloc(os->bufsize + AV_INPUT_BUFFER_PADDING_SIZE);
    os->header        = -1;
    os->start_granule = OGG_NOGRANULE_VALUE;
    if (!os->buf)
        return AVERROR(ENOMEM);

    /* Create the associated AVStream */
    st = avformat_new_stream(s, NULL);
    if (!st) {
        av_freep(&os->buf);
        return AVERROR(ENOMEM);
    }
    st->id = idx;
    avpriv_set_pts_info(st, 64, 1, 1000000);

    ogg->nstreams++;
    return idx;
}