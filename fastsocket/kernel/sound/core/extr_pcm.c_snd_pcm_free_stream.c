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
struct snd_pcm_substream {struct snd_pcm_substream* task_name; struct snd_pcm_substream* next; } ;
struct snd_pcm_str {size_t stream; scalar_t__ pcm; struct snd_pcm_substream* substream; } ;
struct snd_pcm_oss_stream {struct snd_pcm_substream* setup_list; } ;
struct snd_pcm_oss_setup {struct snd_pcm_oss_setup* task_name; struct snd_pcm_oss_setup* next; } ;
struct snd_pcm2 {struct snd_pcm_oss_stream* oss_streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_proc_done (struct snd_pcm_str*) ; 
 int /*<<< orphan*/  snd_pcm_substream_proc_done (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_timer_done (struct snd_pcm_substream*) ; 

__attribute__((used)) static void snd_pcm_free_stream(struct snd_pcm_str * pstr)
{
	struct snd_pcm_substream *substream, *substream_next;
#if defined(CONFIG_SND_PCM_OSS) || defined(CONFIG_SND_PCM_OSS_MODULE)
	struct snd_pcm_oss_setup *setup, *setupn;
#endif
	substream = pstr->substream;
	while (substream) {
		substream_next = substream->next;
		snd_pcm_timer_done(substream);
		snd_pcm_substream_proc_done(substream);
		kfree(substream);
		substream = substream_next;
	}
	snd_pcm_stream_proc_done(pstr);
#if defined(CONFIG_SND_PCM_OSS) || defined(CONFIG_SND_PCM_OSS_MODULE)
	{
		struct snd_pcm_oss_stream *ostr;
		ostr = &((struct snd_pcm2 *)(pstr->pcm))->oss_streams[pstr->stream];
		for (setup = ostr->setup_list; setup; setup = setupn) {
			setupn = setup->next;
			kfree(setup->task_name);
			kfree(setup);
		}
	}
#endif
}