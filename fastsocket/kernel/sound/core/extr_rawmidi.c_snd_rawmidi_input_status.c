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
struct snd_rawmidi_substream {struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_status {scalar_t__ xruns; int /*<<< orphan*/  avail; int /*<<< orphan*/  stream; } ;
struct snd_rawmidi_runtime {int /*<<< orphan*/  lock; scalar_t__ xruns; int /*<<< orphan*/  avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  memset (struct snd_rawmidi_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_rawmidi_input_status(struct snd_rawmidi_substream *substream,
				    struct snd_rawmidi_status * status)
{
	struct snd_rawmidi_runtime *runtime = substream->runtime;

	memset(status, 0, sizeof(*status));
	status->stream = SNDRV_RAWMIDI_STREAM_INPUT;
	spin_lock_irq(&runtime->lock);
	status->avail = runtime->avail;
	status->xruns = runtime->xruns;
	runtime->xruns = 0;
	spin_unlock_irq(&runtime->lock);
	return 0;
}