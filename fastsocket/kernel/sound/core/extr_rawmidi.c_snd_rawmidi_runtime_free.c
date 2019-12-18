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
struct snd_rawmidi_runtime {struct snd_rawmidi_runtime* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_rawmidi_runtime*) ; 

__attribute__((used)) static int snd_rawmidi_runtime_free(struct snd_rawmidi_substream *substream)
{
	struct snd_rawmidi_runtime *runtime = substream->runtime;

	kfree(runtime->buffer);
	kfree(runtime);
	substream->runtime = NULL;
	return 0;
}