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
struct snd_seq_port_subscribe {int dummy; } ;
struct snd_rawmidi_params {int avail_min; int no_active_sensing; int /*<<< orphan*/  buffer_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  output; } ;
struct seq_midisynth {int /*<<< orphan*/  parser; TYPE_1__ output_rfile; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  device; int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_RAWMIDI_LFLG_OUTPUT ; 
 int /*<<< orphan*/  memset (struct snd_rawmidi_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_buffer_size ; 
 int /*<<< orphan*/  snd_midi_event_reset_decode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int snd_rawmidi_kernel_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_rawmidi_kernel_release (TYPE_1__*) ; 
 int snd_rawmidi_output_params (int /*<<< orphan*/ ,struct snd_rawmidi_params*) ; 

__attribute__((used)) static int midisynth_use(void *private_data, struct snd_seq_port_subscribe *info)
{
	int err;
	struct seq_midisynth *msynth = private_data;
	struct snd_rawmidi_params params;

	/* open midi port */
	if ((err = snd_rawmidi_kernel_open(msynth->card, msynth->device,
					   msynth->subdevice,
					   SNDRV_RAWMIDI_LFLG_OUTPUT,
					   &msynth->output_rfile)) < 0) {
		snd_printd("midi output open failed!!!\n");
		return err;
	}
	memset(&params, 0, sizeof(params));
	params.avail_min = 1;
	params.buffer_size = output_buffer_size;
	params.no_active_sensing = 1;
	if ((err = snd_rawmidi_output_params(msynth->output_rfile.output, &params)) < 0) {
		snd_rawmidi_kernel_release(&msynth->output_rfile);
		return err;
	}
	snd_midi_event_reset_decode(msynth->parser);
	return 0;
}