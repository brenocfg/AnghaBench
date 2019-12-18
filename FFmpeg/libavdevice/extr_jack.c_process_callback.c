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
typedef  int /*<<< orphan*/  pkt ;
typedef  scalar_t__ jack_nframes_t ;
struct TYPE_7__ {scalar_t__ max; } ;
typedef  TYPE_1__ jack_latency_range_t ;
struct TYPE_9__ {double pts; scalar_t__ data; } ;
struct TYPE_8__ {double sample_rate; int buffer_size; int pkt_xrun; int nports; int /*<<< orphan*/  packet_count; int /*<<< orphan*/  filled_pkts; int /*<<< orphan*/ * ports; int /*<<< orphan*/  new_pkts; int /*<<< orphan*/  timefilter; int /*<<< orphan*/  client; } ;
typedef  TYPE_2__ JackData ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  JackCaptureLatency ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_write (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int av_fifo_space (int /*<<< orphan*/ ) ; 
 double av_gettime () ; 
 double ff_timefilter_update (int /*<<< orphan*/ ,double,int) ; 
 scalar_t__ jack_frames_since_cycle_start (int /*<<< orphan*/ ) ; 
 float* jack_port_get_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jack_port_get_latency_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_callback(jack_nframes_t nframes, void *arg)
{
    /* Warning: this function runs in realtime. One mustn't allocate memory here
     * or do any other thing that could block. */

    int i, j;
    JackData *self = arg;
    float * buffer;
    jack_nframes_t latency, cycle_delay;
    AVPacket pkt;
    float *pkt_data;
    double cycle_time;

    if (!self->client)
        return 0;

    /* The approximate delay since the hardware interrupt as a number of frames */
    cycle_delay = jack_frames_since_cycle_start(self->client);

    /* Retrieve filtered cycle time */
    cycle_time = ff_timefilter_update(self->timefilter,
                                      av_gettime() / 1000000.0 - (double) cycle_delay / self->sample_rate,
                                      self->buffer_size);

    /* Check if an empty packet is available, and if there's enough space to send it back once filled */
    if ((av_fifo_size(self->new_pkts) < sizeof(pkt)) || (av_fifo_space(self->filled_pkts) < sizeof(pkt))) {
        self->pkt_xrun = 1;
        return 0;
    }

    /* Retrieve empty (but allocated) packet */
    av_fifo_generic_read(self->new_pkts, &pkt, sizeof(pkt), NULL);

    pkt_data  = (float *) pkt.data;
    latency   = 0;

    /* Copy and interleave audio data from the JACK buffer into the packet */
    for (i = 0; i < self->nports; i++) {
        jack_latency_range_t range;
        jack_port_get_latency_range(self->ports[i], JackCaptureLatency, &range);
        latency += range.max;
        buffer = jack_port_get_buffer(self->ports[i], self->buffer_size);
        for (j = 0; j < self->buffer_size; j++)
            pkt_data[j * self->nports + i] = buffer[j];
    }

    /* Timestamp the packet with the cycle start time minus the average latency */
    pkt.pts = (cycle_time - (double) latency / (self->nports * self->sample_rate)) * 1000000.0;

    /* Send the now filled packet back, and increase packet counter */
    av_fifo_generic_write(self->filled_pkts, &pkt, sizeof(pkt), NULL);
    sem_post(&self->packet_count);

    return 0;
}