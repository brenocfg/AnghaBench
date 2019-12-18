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
struct snd_seq_device {int device; struct snd_card* card; } ;
struct snd_card {size_t number; } ;
struct seq_midisynth_client {int* ports_per_device; scalar_t__ num_ports; int /*<<< orphan*/  seq_client; struct seq_midisynth_client** ports; } ;
struct seq_midisynth {int* ports_per_device; scalar_t__ num_ports; int /*<<< orphan*/  seq_client; struct seq_midisynth** ports; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kfree (struct seq_midisynth_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 int /*<<< orphan*/  snd_seq_delete_kernel_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_midisynth_delete (struct seq_midisynth_client*) ; 
 struct seq_midisynth_client** synths ; 

__attribute__((used)) static int
snd_seq_midisynth_unregister_port(struct snd_seq_device *dev)
{
	struct seq_midisynth_client *client;
	struct seq_midisynth *msynth;
	struct snd_card *card = dev->card;
	int device = dev->device, p, ports;
	
	mutex_lock(&register_mutex);
	client = synths[card->number];
	if (client == NULL || client->ports[device] == NULL) {
		mutex_unlock(&register_mutex);
		return -ENODEV;
	}
	ports = client->ports_per_device[device];
	client->ports_per_device[device] = 0;
	msynth = client->ports[device];
	client->ports[device] = NULL;
	for (p = 0; p < ports; p++)
		snd_seq_midisynth_delete(&msynth[p]);
	kfree(msynth);
	client->num_ports--;
	if (client->num_ports <= 0) {
		snd_seq_delete_kernel_client(client->seq_client);
		synths[card->number] = NULL;
		kfree(client);
	}
	mutex_unlock(&register_mutex);
	return 0;
}