#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_port_subscribe {int dummy; } ;
struct snd_rawmidi_runtime {struct seq_midisynth* private_data; int /*<<< orphan*/  event; } ;
struct snd_rawmidi_params {int avail_min; int /*<<< orphan*/  buffer_size; } ;
struct TYPE_5__ {TYPE_2__* input; } ;
struct seq_midisynth {TYPE_1__ input_rfile; int /*<<< orphan*/  parser; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  device; int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_6__ {struct snd_rawmidi_runtime* runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_RAWMIDI_LFLG_INPUT ; 
 int /*<<< orphan*/  input_buffer_size ; 
 int /*<<< orphan*/  memset (struct snd_rawmidi_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_midi_event_reset_encode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_midi_input_event ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int snd_rawmidi_input_params (TYPE_2__*,struct snd_rawmidi_params*) ; 
 int snd_rawmidi_kernel_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_rawmidi_kernel_read (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_kernel_release (TYPE_1__*) ; 

__attribute__((used)) static int midisynth_subscribe(void *private_data, struct snd_seq_port_subscribe *info)
{
	int err;
	struct seq_midisynth *msynth = private_data;
	struct snd_rawmidi_runtime *runtime;
	struct snd_rawmidi_params params;

	/* open midi port */
	if ((err = snd_rawmidi_kernel_open(msynth->card, msynth->device,
					   msynth->subdevice,
					   SNDRV_RAWMIDI_LFLG_INPUT,
					   &msynth->input_rfile)) < 0) {
		snd_printd("midi input open failed!!!\n");
		return err;
	}
	runtime = msynth->input_rfile.input->runtime;
	memset(&params, 0, sizeof(params));
	params.avail_min = 1;
	params.buffer_size = input_buffer_size;
	if ((err = snd_rawmidi_input_params(msynth->input_rfile.input, &params)) < 0) {
		snd_rawmidi_kernel_release(&msynth->input_rfile);
		return err;
	}
	snd_midi_event_reset_encode(msynth->parser);
	runtime->event = snd_midi_input_event;
	runtime->private_data = msynth;
	snd_rawmidi_kernel_read(msynth->input_rfile.input, NULL, 0);
	return 0;
}