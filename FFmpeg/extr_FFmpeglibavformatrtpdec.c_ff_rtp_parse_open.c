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
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int payload_type; int queue_size; int /*<<< orphan*/  hostname; int /*<<< orphan*/  statistics; int /*<<< orphan*/ * ic; TYPE_3__* st; void* first_rtcp_ntp_time; void* last_rtcp_ntp_time; } ;
struct TYPE_7__ {int codec_id; int sample_rate; } ;
typedef  TYPE_2__ RTPDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
#define  AV_CODEC_ID_ADPCM_G722 128 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* av_mallocz (int) ; 
 int /*<<< orphan*/  gethostname (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtp_init_statistics (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

RTPDemuxContext *ff_rtp_parse_open(AVFormatContext *s1, AVStream *st,
                                   int payload_type, int queue_size)
{
    RTPDemuxContext *s;

    s = av_mallocz(sizeof(RTPDemuxContext));
    if (!s)
        return NULL;
    s->payload_type        = payload_type;
    s->last_rtcp_ntp_time  = AV_NOPTS_VALUE;
    s->first_rtcp_ntp_time = AV_NOPTS_VALUE;
    s->ic                  = s1;
    s->st                  = st;
    s->queue_size          = queue_size;

    av_log(s->ic, AV_LOG_VERBOSE, "setting jitter buffer size to %d\n",
           s->queue_size);

    rtp_init_statistics(&s->statistics, 0);
    if (st) {
        switch (st->codecpar->codec_id) {
        case AV_CODEC_ID_ADPCM_G722:
            /* According to RFC 3551, the stream clock rate is 8000
             * even if the sample rate is 16000. */
            if (st->codecpar->sample_rate == 8000)
                st->codecpar->sample_rate = 16000;
            break;
        default:
            break;
        }
    }
    // needed to send back RTCP RR in RTSP sessions
    gethostname(s->hostname, sizeof(s->hostname));
    return s;
}