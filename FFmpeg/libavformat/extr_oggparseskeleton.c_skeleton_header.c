#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct ogg_stream {int pstart; int flags; int psize; int lastpts; scalar_t__ start_granule; int /*<<< orphan*/ * buf; } ;
struct ogg {struct ogg_stream* streams; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {TYPE_2__** streams; struct ogg* priv_data; } ;
struct TYPE_8__ {int start_time; TYPE_1__* codecpar; } ;
struct TYPE_7__ {int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_DATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_RL32 (int /*<<< orphan*/ *) ; 
 scalar_t__ AV_RL64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int OGG_FLAG_EOS ; 
 scalar_t__ OGG_NOGRANULE_VALUE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_reduce (int*,int*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 int ogg_find_stream (struct ogg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int skeleton_header(AVFormatContext *s, int idx)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    AVStream *st = s->streams[idx];
    uint8_t *buf = os->buf + os->pstart;
    int version_major, version_minor;
    int64_t start_num, start_den;
    uint64_t start_granule;
    int target_idx, start_time;

    st->codecpar->codec_type = AVMEDIA_TYPE_DATA;

    if ((os->flags & OGG_FLAG_EOS) && os->psize == 0)
        return 1;

    if (os->psize < 8)
        return -1;

    if (!strncmp(buf, "fishead", 8)) {
        if (os->psize < 64)
            return -1;

        version_major = AV_RL16(buf+8);
        version_minor = AV_RL16(buf+10);

        if (version_major != 3 && version_major != 4) {
            av_log(s, AV_LOG_WARNING, "Unknown skeleton version %d.%d\n",
                   version_major, version_minor);
            return -1;
        }

        // This is the overall start time. We use it for the start time of
        // of the skeleton stream since if left unset lavf assumes 0,
        // which we don't want since skeleton is timeless
        // FIXME: the real meaning of this field is "start playback at
        // this time which can be in the middle of a packet
        start_num = AV_RL64(buf+12);
        start_den = AV_RL64(buf+20);

        if (start_den > 0 && start_num > 0) {
            int base_den;
            av_reduce(&start_time, &base_den, start_num, start_den, INT_MAX);
            avpriv_set_pts_info(st, 64, 1, base_den);
            os->lastpts =
            st->start_time = start_time;
        }
    } else if (!strncmp(buf, "fisbone", 8)) {
        if (os->psize < 52)
            return -1;

        target_idx = ogg_find_stream(ogg, AV_RL32(buf+12));
        start_granule = AV_RL64(buf+36);
        if (target_idx < 0) {
            av_log(s, AV_LOG_WARNING, "Serial number in fisbone doesn't match any stream\n");
            return 1;
        }
        os = ogg->streams + target_idx;
        if (os->start_granule != OGG_NOGRANULE_VALUE) {
            av_log(s, AV_LOG_WARNING, "Multiple fisbone for the same stream\n");
            return 1;
        }
        if (start_granule != OGG_NOGRANULE_VALUE) {
            os->start_granule = start_granule;
        }
    }

    return 1;
}