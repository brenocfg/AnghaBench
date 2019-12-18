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
struct snd_seq_event {int dummy; } ;
struct snd_emux_port {int /*<<< orphan*/  chset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  emux_ops ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_midi_process_event (int /*<<< orphan*/ *,struct snd_seq_event*,int /*<<< orphan*/ *) ; 

int
snd_emux_event_input(struct snd_seq_event *ev, int direct, void *private_data,
		     int atomic, int hop)
{
	struct snd_emux_port *port;

	port = private_data;
	if (snd_BUG_ON(!port || !ev))
		return -EINVAL;

	snd_midi_process_event(&emux_ops, ev, &port->chset);

	return 0;
}