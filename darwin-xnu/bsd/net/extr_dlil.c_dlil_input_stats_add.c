#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ifnet_stat_increment_param {scalar_t__ packets_in; scalar_t__ bytes_in; scalar_t__ errors_in; scalar_t__ packets_out; scalar_t__ bytes_out; scalar_t__ errors_out; scalar_t__ collisions; scalar_t__ dropped; } ;
struct dlil_threading_info {int /*<<< orphan*/  tstats; struct ifnet_stat_increment_param stats; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  PKTCNTR_ADD (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
dlil_input_stats_add(const struct ifnet_stat_increment_param *s,
    struct dlil_threading_info *inp, boolean_t poll)
{
	struct ifnet_stat_increment_param *d = &inp->stats;

	if (s->packets_in != 0)
		d->packets_in += s->packets_in;
	if (s->bytes_in != 0)
		d->bytes_in += s->bytes_in;
	if (s->errors_in != 0)
		d->errors_in += s->errors_in;

	if (s->packets_out != 0)
		d->packets_out += s->packets_out;
	if (s->bytes_out != 0)
		d->bytes_out += s->bytes_out;
	if (s->errors_out != 0)
		d->errors_out += s->errors_out;

	if (s->collisions != 0)
		d->collisions += s->collisions;
	if (s->dropped != 0)
		d->dropped += s->dropped;

	if (poll)
		PKTCNTR_ADD(&inp->tstats, s->packets_in, s->bytes_in);
}