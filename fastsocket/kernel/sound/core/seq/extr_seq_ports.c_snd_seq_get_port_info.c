#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_port_info {int /*<<< orphan*/  time_queue; int /*<<< orphan*/  flags; int /*<<< orphan*/  write_use; int /*<<< orphan*/  read_use; int /*<<< orphan*/  synth_voices; int /*<<< orphan*/  midi_voices; int /*<<< orphan*/  midi_channels; int /*<<< orphan*/  type; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct snd_seq_client_port {int /*<<< orphan*/  time_queue; scalar_t__ time_real; scalar_t__ timestamping; TYPE_2__ c_dest; TYPE_1__ c_src; int /*<<< orphan*/  synth_voices; int /*<<< orphan*/  midi_voices; int /*<<< orphan*/  midi_channels; int /*<<< orphan*/  type; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_SEQ_PORT_FLG_TIMESTAMP ; 
 int /*<<< orphan*/  SNDRV_SEQ_PORT_FLG_TIME_REAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int snd_seq_get_port_info(struct snd_seq_client_port * port,
			  struct snd_seq_port_info * info)
{
	if (snd_BUG_ON(!port || !info))
		return -EINVAL;

	/* get port name */
	strlcpy(info->name, port->name, sizeof(info->name));
	
	/* get capabilities */
	info->capability = port->capability;

	/* get port type */
	info->type = port->type;

	/* information about supported channels/voices */
	info->midi_channels = port->midi_channels;
	info->midi_voices = port->midi_voices;
	info->synth_voices = port->synth_voices;

	/* get subscriber counts */
	info->read_use = port->c_src.count;
	info->write_use = port->c_dest.count;
	
	/* timestamping */
	info->flags = 0;
	if (port->timestamping) {
		info->flags |= SNDRV_SEQ_PORT_FLG_TIMESTAMP;
		if (port->time_real)
			info->flags |= SNDRV_SEQ_PORT_FLG_TIME_REAL;
		info->time_queue = port->time_queue;
	}

	return 0;
}