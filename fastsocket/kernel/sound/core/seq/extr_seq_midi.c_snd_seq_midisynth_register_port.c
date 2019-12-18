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
struct TYPE_4__ {scalar_t__ client; int port; } ;
struct snd_seq_port_info {int device; unsigned int subdevice; unsigned int subdevices_count; scalar_t__ seq_client; int flags; char* name; int capability; int type; int midi_channels; int seq_port; unsigned int* ports_per_device; int /*<<< orphan*/  num_ports; struct snd_seq_port_info** ports; TYPE_2__ addr; struct snd_seq_port_info* kernel; int /*<<< orphan*/  event_input; int /*<<< orphan*/  unuse; int /*<<< orphan*/  use; int /*<<< orphan*/  unsubscribe; int /*<<< orphan*/  subscribe; struct snd_seq_port_info* private_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  subname; void* stream; } ;
struct snd_seq_port_callback {int device; unsigned int subdevice; unsigned int subdevices_count; scalar_t__ seq_client; int flags; char* name; int capability; int type; int midi_channels; int seq_port; unsigned int* ports_per_device; int /*<<< orphan*/  num_ports; struct snd_seq_port_callback** ports; TYPE_2__ addr; struct snd_seq_port_callback* kernel; int /*<<< orphan*/  event_input; int /*<<< orphan*/  unuse; int /*<<< orphan*/  use; int /*<<< orphan*/  unsubscribe; int /*<<< orphan*/  subscribe; struct snd_seq_port_callback* private_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  subname; void* stream; } ;
struct snd_seq_device {int device; struct snd_card* card; struct snd_rawmidi* private_data; } ;
struct snd_rawmidi_info {int device; unsigned int subdevice; unsigned int subdevices_count; scalar_t__ seq_client; int flags; char* name; int capability; int type; int midi_channels; int seq_port; unsigned int* ports_per_device; int /*<<< orphan*/  num_ports; struct snd_rawmidi_info** ports; TYPE_2__ addr; struct snd_rawmidi_info* kernel; int /*<<< orphan*/  event_input; int /*<<< orphan*/  unuse; int /*<<< orphan*/  use; int /*<<< orphan*/  unsubscribe; int /*<<< orphan*/  subscribe; struct snd_rawmidi_info* private_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  subname; void* stream; } ;
struct snd_rawmidi {TYPE_1__* ops; } ;
struct snd_card {size_t number; scalar_t__* shortname; } ;
struct seq_midisynth_client {int device; unsigned int subdevice; unsigned int subdevices_count; scalar_t__ seq_client; int flags; char* name; int capability; int type; int midi_channels; int seq_port; unsigned int* ports_per_device; int /*<<< orphan*/  num_ports; struct seq_midisynth_client** ports; TYPE_2__ addr; struct seq_midisynth_client* kernel; int /*<<< orphan*/  event_input; int /*<<< orphan*/  unuse; int /*<<< orphan*/  use; int /*<<< orphan*/  unsubscribe; int /*<<< orphan*/  subscribe; struct seq_midisynth_client* private_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  subname; void* stream; } ;
struct seq_midisynth {int device; unsigned int subdevice; unsigned int subdevices_count; scalar_t__ seq_client; int flags; char* name; int capability; int type; int midi_channels; int seq_port; unsigned int* ports_per_device; int /*<<< orphan*/  num_ports; struct seq_midisynth** ports; TYPE_2__ addr; struct seq_midisynth* kernel; int /*<<< orphan*/  event_input; int /*<<< orphan*/  unuse; int /*<<< orphan*/  use; int /*<<< orphan*/  unsubscribe; int /*<<< orphan*/  subscribe; struct seq_midisynth* private_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  subname; void* stream; } ;
typedef  int /*<<< orphan*/  pcallbacks ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_port_info ) (struct snd_rawmidi*,unsigned int,struct snd_seq_port_info*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_RAWMIDI_DEVICES ; 
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 void* SNDRV_RAWMIDI_STREAM_INPUT ; 
 void* SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_CREATE_PORT ; 
 int SNDRV_SEQ_PORT_CAP_DUPLEX ; 
 int SNDRV_SEQ_PORT_CAP_READ ; 
 int SNDRV_SEQ_PORT_CAP_SUBS_READ ; 
 int SNDRV_SEQ_PORT_CAP_SUBS_WRITE ; 
 int SNDRV_SEQ_PORT_CAP_SYNC_READ ; 
 int SNDRV_SEQ_PORT_CAP_SYNC_WRITE ; 
 int SNDRV_SEQ_PORT_CAP_WRITE ; 
 int SNDRV_SEQ_PORT_FLG_GIVEN_PORT ; 
 int SNDRV_SEQ_PORT_TYPE_HARDWARE ; 
 int SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC ; 
 int SNDRV_SEQ_PORT_TYPE_PORT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  event_process_midi ; 
 struct snd_seq_port_info* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_seq_port_info*) ; 
 struct snd_seq_port_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_seq_port_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct snd_seq_port_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  midisynth_subscribe ; 
 int /*<<< orphan*/  midisynth_unsubscribe ; 
 int /*<<< orphan*/  midisynth_unuse ; 
 int /*<<< orphan*/  midisynth_use ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__ snd_rawmidi_info_select (struct snd_card*,struct snd_seq_port_info*) ; 
 scalar_t__ snd_seq_create_kernel_client (struct snd_card*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  snd_seq_delete_kernel_client (scalar_t__) ; 
 scalar_t__ snd_seq_kernel_client_ctl (scalar_t__,int /*<<< orphan*/ ,struct snd_seq_port_info*) ; 
 int /*<<< orphan*/  snd_seq_midisynth_delete (struct snd_seq_port_info*) ; 
 scalar_t__ snd_seq_midisynth_new (struct snd_seq_port_info*,struct snd_card*,int,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_rawmidi*,unsigned int,struct snd_seq_port_info*) ; 
 struct snd_seq_port_info** synths ; 

__attribute__((used)) static int
snd_seq_midisynth_register_port(struct snd_seq_device *dev)
{
	struct seq_midisynth_client *client;
	struct seq_midisynth *msynth, *ms;
	struct snd_seq_port_info *port;
	struct snd_rawmidi_info *info;
	struct snd_rawmidi *rmidi = dev->private_data;
	int newclient = 0;
	unsigned int p, ports;
	struct snd_seq_port_callback pcallbacks;
	struct snd_card *card = dev->card;
	int device = dev->device;
	unsigned int input_count = 0, output_count = 0;

	if (snd_BUG_ON(!card || device < 0 || device >= SNDRV_RAWMIDI_DEVICES))
		return -EINVAL;
	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (! info)
		return -ENOMEM;
	info->device = device;
	info->stream = SNDRV_RAWMIDI_STREAM_OUTPUT;
	info->subdevice = 0;
	if (snd_rawmidi_info_select(card, info) >= 0)
		output_count = info->subdevices_count;
	info->stream = SNDRV_RAWMIDI_STREAM_INPUT;
	if (snd_rawmidi_info_select(card, info) >= 0) {
		input_count = info->subdevices_count;
	}
	ports = output_count;
	if (ports < input_count)
		ports = input_count;
	if (ports == 0) {
		kfree(info);
		return -ENODEV;
	}
	if (ports > (256 / SNDRV_RAWMIDI_DEVICES))
		ports = 256 / SNDRV_RAWMIDI_DEVICES;

	mutex_lock(&register_mutex);
	client = synths[card->number];
	if (client == NULL) {
		newclient = 1;
		client = kzalloc(sizeof(*client), GFP_KERNEL);
		if (client == NULL) {
			mutex_unlock(&register_mutex);
			kfree(info);
			return -ENOMEM;
		}
		client->seq_client =
			snd_seq_create_kernel_client(
				card, 0, "%s", card->shortname[0] ?
				(const char *)card->shortname : "External MIDI");
		if (client->seq_client < 0) {
			kfree(client);
			mutex_unlock(&register_mutex);
			kfree(info);
			return -ENOMEM;
		}
	}

	msynth = kcalloc(ports, sizeof(struct seq_midisynth), GFP_KERNEL);
	port = kmalloc(sizeof(*port), GFP_KERNEL);
	if (msynth == NULL || port == NULL)
		goto __nomem;

	for (p = 0; p < ports; p++) {
		ms = &msynth[p];

		if (snd_seq_midisynth_new(ms, card, device, p) < 0)
			goto __nomem;

		/* declare port */
		memset(port, 0, sizeof(*port));
		port->addr.client = client->seq_client;
		port->addr.port = device * (256 / SNDRV_RAWMIDI_DEVICES) + p;
		port->flags = SNDRV_SEQ_PORT_FLG_GIVEN_PORT;
		memset(info, 0, sizeof(*info));
		info->device = device;
		if (p < output_count)
			info->stream = SNDRV_RAWMIDI_STREAM_OUTPUT;
		else
			info->stream = SNDRV_RAWMIDI_STREAM_INPUT;
		info->subdevice = p;
		if (snd_rawmidi_info_select(card, info) >= 0)
			strcpy(port->name, info->subname);
		if (! port->name[0]) {
			if (info->name[0]) {
				if (ports > 1)
					snprintf(port->name, sizeof(port->name), "%s-%d", info->name, p);
				else
					snprintf(port->name, sizeof(port->name), "%s", info->name);
			} else {
				/* last resort */
				if (ports > 1)
					sprintf(port->name, "MIDI %d-%d-%d", card->number, device, p);
				else
					sprintf(port->name, "MIDI %d-%d", card->number, device);
			}
		}
		if ((info->flags & SNDRV_RAWMIDI_INFO_OUTPUT) && p < output_count)
			port->capability |= SNDRV_SEQ_PORT_CAP_WRITE | SNDRV_SEQ_PORT_CAP_SYNC_WRITE | SNDRV_SEQ_PORT_CAP_SUBS_WRITE;
		if ((info->flags & SNDRV_RAWMIDI_INFO_INPUT) && p < input_count)
			port->capability |= SNDRV_SEQ_PORT_CAP_READ | SNDRV_SEQ_PORT_CAP_SYNC_READ | SNDRV_SEQ_PORT_CAP_SUBS_READ;
		if ((port->capability & (SNDRV_SEQ_PORT_CAP_WRITE|SNDRV_SEQ_PORT_CAP_READ)) == (SNDRV_SEQ_PORT_CAP_WRITE|SNDRV_SEQ_PORT_CAP_READ) &&
		    info->flags & SNDRV_RAWMIDI_INFO_DUPLEX)
			port->capability |= SNDRV_SEQ_PORT_CAP_DUPLEX;
		port->type = SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
			| SNDRV_SEQ_PORT_TYPE_HARDWARE
			| SNDRV_SEQ_PORT_TYPE_PORT;
		port->midi_channels = 16;
		memset(&pcallbacks, 0, sizeof(pcallbacks));
		pcallbacks.owner = THIS_MODULE;
		pcallbacks.private_data = ms;
		pcallbacks.subscribe = midisynth_subscribe;
		pcallbacks.unsubscribe = midisynth_unsubscribe;
		pcallbacks.use = midisynth_use;
		pcallbacks.unuse = midisynth_unuse;
		pcallbacks.event_input = event_process_midi;
		port->kernel = &pcallbacks;
		if (rmidi->ops && rmidi->ops->get_port_info)
			rmidi->ops->get_port_info(rmidi, p, port);
		if (snd_seq_kernel_client_ctl(client->seq_client, SNDRV_SEQ_IOCTL_CREATE_PORT, port)<0)
			goto __nomem;
		ms->seq_client = client->seq_client;
		ms->seq_port = port->addr.port;
	}
	client->ports_per_device[device] = ports;
	client->ports[device] = msynth;
	client->num_ports++;
	if (newclient)
		synths[card->number] = client;
	mutex_unlock(&register_mutex);
	kfree(info);
	kfree(port);
	return 0;	/* success */

      __nomem:
	if (msynth != NULL) {
	      	for (p = 0; p < ports; p++)
	      		snd_seq_midisynth_delete(&msynth[p]);
		kfree(msynth);
	}
	if (newclient) {
		snd_seq_delete_kernel_client(client->seq_client);
		kfree(client);
	}
	kfree(info);
	kfree(port);
	mutex_unlock(&register_mutex);
	return -ENOMEM;
}