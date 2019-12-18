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
struct snd_seq_port_callback {struct snd_opl4* private_data; int /*<<< orphan*/  private_free; int /*<<< orphan*/  event_input; int /*<<< orphan*/  unuse; int /*<<< orphan*/  use; int /*<<< orphan*/  owner; } ;
struct snd_seq_device {int dummy; } ;
struct snd_opl4 {int seq_client; TYPE_1__* chset; int /*<<< orphan*/  seq_dev_num; int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  pcallbacks ;
struct TYPE_3__ {int client; int port; struct snd_opl4* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ SNDRV_SEQ_DEVICE_ARGPTR (struct snd_seq_device*) ; 
 int SNDRV_SEQ_PORT_CAP_SUBS_WRITE ; 
 int SNDRV_SEQ_PORT_CAP_WRITE ; 
 int SNDRV_SEQ_PORT_TYPE_HARDWARE ; 
 int SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC ; 
 int SNDRV_SEQ_PORT_TYPE_MIDI_GM ; 
 int SNDRV_SEQ_PORT_TYPE_SYNTHESIZER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  memset (struct snd_seq_port_callback*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* snd_midi_channel_alloc_set (int) ; 
 int /*<<< orphan*/  snd_midi_channel_free_set (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_opl4_seq_event_input ; 
 int /*<<< orphan*/  snd_opl4_seq_free_port ; 
 int /*<<< orphan*/  snd_opl4_seq_unuse ; 
 int /*<<< orphan*/  snd_opl4_seq_use ; 
 int snd_seq_create_kernel_client (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_seq_delete_kernel_client (int) ; 
 int snd_seq_event_port_attach (int,struct snd_seq_port_callback*,int,int,int,int,char*) ; 
 scalar_t__ snd_yrw801_detect (struct snd_opl4*) ; 

__attribute__((used)) static int snd_opl4_seq_new_device(struct snd_seq_device *dev)
{
	struct snd_opl4 *opl4;
	int client;
	struct snd_seq_port_callback pcallbacks;

	opl4 = *(struct snd_opl4 **)SNDRV_SEQ_DEVICE_ARGPTR(dev);
	if (!opl4)
		return -EINVAL;

	if (snd_yrw801_detect(opl4) < 0)
		return -ENODEV;

	opl4->chset = snd_midi_channel_alloc_set(16);
	if (!opl4->chset)
		return -ENOMEM;
	opl4->chset->private_data = opl4;

	/* allocate new client */
	client = snd_seq_create_kernel_client(opl4->card, opl4->seq_dev_num,
					      "OPL4 Wavetable");
	if (client < 0) {
		snd_midi_channel_free_set(opl4->chset);
		return client;
	}
	opl4->seq_client = client;
	opl4->chset->client = client;

	/* create new port */
	memset(&pcallbacks, 0, sizeof(pcallbacks));
	pcallbacks.owner = THIS_MODULE;
	pcallbacks.use = snd_opl4_seq_use;
	pcallbacks.unuse = snd_opl4_seq_unuse;
	pcallbacks.event_input = snd_opl4_seq_event_input;
	pcallbacks.private_free = snd_opl4_seq_free_port;
	pcallbacks.private_data = opl4;

	opl4->chset->port = snd_seq_event_port_attach(client, &pcallbacks,
						      SNDRV_SEQ_PORT_CAP_WRITE |
						      SNDRV_SEQ_PORT_CAP_SUBS_WRITE,
						      SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |
						      SNDRV_SEQ_PORT_TYPE_MIDI_GM |
						      SNDRV_SEQ_PORT_TYPE_HARDWARE |
						      SNDRV_SEQ_PORT_TYPE_SYNTHESIZER,
						      16, 24,
						      "OPL4 Wavetable Port");
	if (opl4->chset->port < 0) {
		int err = opl4->chset->port;
		snd_midi_channel_free_set(opl4->chset);
		snd_seq_delete_kernel_client(client);
		opl4->seq_client = -1;
		return err;
	}
	return 0;
}