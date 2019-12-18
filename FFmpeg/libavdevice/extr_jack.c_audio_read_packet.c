#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_sec; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int activated; int /*<<< orphan*/  filled_pkts; scalar_t__ jack_xrun; scalar_t__ pkt_xrun; int /*<<< orphan*/  client; int /*<<< orphan*/  packet_count; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_1__ JackData ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (scalar_t__) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ EIO ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int av_gettime () ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  jack_activate (int /*<<< orphan*/ ) ; 
 scalar_t__ sem_timedwait (int /*<<< orphan*/ *,struct timespec*) ; 
 int supply_new_packets (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int audio_read_packet(AVFormatContext *context, AVPacket *pkt)
{
    JackData *self = context->priv_data;
    struct timespec timeout = {0, 0};
    int test;

    /* Activate the JACK client on first packet read. Activating the JACK client
     * means that process_callback() starts to get called at regular interval.
     * If we activate it in audio_read_header(), we're actually reading audio data
     * from the device before instructed to, and that may result in an overrun. */
    if (!self->activated) {
        if (!jack_activate(self->client)) {
            self->activated = 1;
            av_log(context, AV_LOG_INFO,
                   "JACK client registered and activated (rate=%dHz, buffer_size=%d frames)\n",
                   self->sample_rate, self->buffer_size);
        } else {
            av_log(context, AV_LOG_ERROR, "Unable to activate JACK client\n");
            return AVERROR(EIO);
        }
    }

    /* Wait for a packet coming back from process_callback(), if one isn't available yet */
    timeout.tv_sec = av_gettime() / 1000000 + 2;
    if (sem_timedwait(&self->packet_count, &timeout)) {
        if (errno == ETIMEDOUT) {
            av_log(context, AV_LOG_ERROR,
                   "Input error: timed out when waiting for JACK process callback output\n");
        } else {
            char errbuf[128];
            int ret = AVERROR(errno);
            av_strerror(ret, errbuf, sizeof(errbuf));
            av_log(context, AV_LOG_ERROR, "Error while waiting for audio packet: %s\n",
                   errbuf);
        }
        if (!self->client)
            av_log(context, AV_LOG_ERROR, "Input error: JACK server is gone\n");

        return AVERROR(EIO);
    }

    if (self->pkt_xrun) {
        av_log(context, AV_LOG_WARNING, "Audio packet xrun\n");
        self->pkt_xrun = 0;
    }

    if (self->jack_xrun) {
        av_log(context, AV_LOG_WARNING, "JACK xrun\n");
        self->jack_xrun = 0;
    }

    /* Retrieve the packet filled with audio data by process_callback() */
    av_fifo_generic_read(self->filled_pkts, pkt, sizeof(*pkt), NULL);

    if ((test = supply_new_packets(self, context)))
        return test;

    return 0;
}