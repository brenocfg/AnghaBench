#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  timefilter; int /*<<< orphan*/  ports; int /*<<< orphan*/  filled_pkts; int /*<<< orphan*/  new_pkts; int /*<<< orphan*/  packet_count; scalar_t__ client; scalar_t__ activated; } ;
typedef  TYPE_1__ JackData ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_timefilter_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pkt_fifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jack_client_close (scalar_t__) ; 
 int /*<<< orphan*/  jack_deactivate (scalar_t__) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_jack(JackData *self)
{
    if (self->client) {
        if (self->activated)
            jack_deactivate(self->client);
        jack_client_close(self->client);
    }
    sem_destroy(&self->packet_count);
    free_pkt_fifo(&self->new_pkts);
    free_pkt_fifo(&self->filled_pkts);
    av_freep(&self->ports);
    ff_timefilter_destroy(self->timefilter);
}