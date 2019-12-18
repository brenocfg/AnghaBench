#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_port_subscribe {int dummy; } ;
struct TYPE_7__ {int channel; int /*<<< orphan*/  param; } ;
struct TYPE_8__ {TYPE_3__ control; } ;
struct TYPE_6__ {int /*<<< orphan*/  client; } ;
struct TYPE_5__ {int /*<<< orphan*/  port; } ;
struct snd_seq_event {TYPE_4__ data; int /*<<< orphan*/  type; TYPE_2__ dest; TYPE_1__ source; } ;
struct snd_seq_dummy_port {int /*<<< orphan*/  client; int /*<<< orphan*/  port; int /*<<< orphan*/  connect; scalar_t__ duplex; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  MIDI_CTL_ALL_SOUNDS_OFF ; 
 int /*<<< orphan*/  MIDI_CTL_RESET_CONTROLLERS ; 
 int /*<<< orphan*/  SNDRV_SEQ_ADDRESS_SUBSCRIBERS ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CONTROLLER ; 
 int /*<<< orphan*/  memset (struct snd_seq_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_kernel_client_dispatch (int /*<<< orphan*/ ,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dummy_unuse(void *private_data, struct snd_seq_port_subscribe *info)
{
	struct snd_seq_dummy_port *p;
	int i;
	struct snd_seq_event ev;

	p = private_data;
	memset(&ev, 0, sizeof(ev));
	if (p->duplex)
		ev.source.port = p->connect;
	else
		ev.source.port = p->port;
	ev.dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
	ev.type = SNDRV_SEQ_EVENT_CONTROLLER;
	for (i = 0; i < 16; i++) {
		ev.data.control.channel = i;
		ev.data.control.param = MIDI_CTL_ALL_SOUNDS_OFF;
		snd_seq_kernel_client_dispatch(p->client, &ev, 0, 0);
		ev.data.control.param = MIDI_CTL_RESET_CONTROLLERS;
		snd_seq_kernel_client_dispatch(p->client, &ev, 0, 0);
	}
	return 0;
}