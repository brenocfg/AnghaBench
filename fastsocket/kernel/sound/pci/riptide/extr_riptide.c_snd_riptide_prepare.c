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
struct snd_riptide {int /*<<< orphan*/  lock; struct cmdif* cif; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int channels; unsigned int format; unsigned int rate; int /*<<< orphan*/  period_size; int /*<<< orphan*/  buffer_size; } ;
struct sgd {void* dwSegLen; void* dwStat_Ctl; void* dwSegPtrPhys; void* dwNextLink; } ;
struct TYPE_4__ {unsigned int addr; scalar_t__ area; } ;
struct TYPE_3__ {unsigned char* noconv; unsigned char* mono; unsigned char* stereo; } ;
struct pcmhw {unsigned int id; unsigned int size; unsigned int pages; unsigned char* lbuspath; unsigned int rate; scalar_t__ format; unsigned int channels; int /*<<< orphan*/  intdec; int /*<<< orphan*/  mixer; int /*<<< orphan*/  source; struct sgd* sgdbuf; TYPE_2__ sgdlist; TYPE_1__ paths; } ;
struct cmdif {int dummy; } ;
typedef  scalar_t__ snd_pcm_format_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 unsigned int IEOB_ENABLE ; 
 unsigned int IEOC_ENABLE ; 
 unsigned int IEOS_ENABLE ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ SNDRV_PCM_FORMAT_S16_LE ; 
 int /*<<< orphan*/  alloclbuspath (struct cmdif*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (unsigned int) ; 
 unsigned int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freelbuspath (struct cmdif*,int /*<<< orphan*/ ,unsigned char*) ; 
 struct pcmhw* get_pcmhwdev (struct snd_pcm_substream*) ; 
 scalar_t__ setsampleformat (struct cmdif*,int /*<<< orphan*/ ,unsigned int,unsigned int,scalar_t__) ; 
 scalar_t__ setsamplerate (struct cmdif*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 unsigned int snd_pcm_sgbuf_get_addr (struct snd_pcm_substream*,unsigned int) ; 
 struct snd_riptide* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned int,...) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_riptide_prepare(struct snd_pcm_substream *substream)
{
	struct snd_riptide *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct pcmhw *data = get_pcmhwdev(substream);
	struct cmdif *cif = chip->cif;
	unsigned char *lbuspath = NULL;
	unsigned int rate, channels;
	int err = 0;
	snd_pcm_format_t format;

	if (snd_BUG_ON(!cif || !data))
		return -EINVAL;

	snd_printdd("prepare id %d ch: %d f:0x%x r:%d\n", data->id,
		    runtime->channels, runtime->format, runtime->rate);

	spin_lock_irq(&chip->lock);
	channels = runtime->channels;
	format = runtime->format;
	rate = runtime->rate;
	switch (channels) {
	case 1:
		if (rate == 48000 && format == SNDRV_PCM_FORMAT_S16_LE)
			lbuspath = data->paths.noconv;
		else
			lbuspath = data->paths.mono;
		break;
	case 2:
		if (rate == 48000 && format == SNDRV_PCM_FORMAT_S16_LE)
			lbuspath = data->paths.noconv;
		else
			lbuspath = data->paths.stereo;
		break;
	}
	snd_printdd("use sgdlist at 0x%p\n",
		    data->sgdlist.area);
	if (data->sgdlist.area) {
		unsigned int i, j, size, pages, f, pt, period;
		struct sgd *c, *p = NULL;

		size = frames_to_bytes(runtime, runtime->buffer_size);
		period = frames_to_bytes(runtime, runtime->period_size);
		f = PAGE_SIZE;
		while ((size + (f >> 1) - 1) <= (f << 7) && (f << 1) > period)
			f = f >> 1;
		pages = (size + f - 1) / f;
		data->size = size;
		data->pages = pages;
		snd_printdd
		    ("create sgd size: 0x%x pages %d of size 0x%x for period 0x%x\n",
		     size, pages, f, period);
		pt = 0;
		j = 0;
		for (i = 0; i < pages; i++) {
			unsigned int ofs, addr;
			c = &data->sgdbuf[i];
			if (p)
				p->dwNextLink = cpu_to_le32(data->sgdlist.addr +
							    (i *
							     sizeof(struct
								    sgd)));
			c->dwNextLink = cpu_to_le32(data->sgdlist.addr);
			ofs = j << PAGE_SHIFT;
			addr = snd_pcm_sgbuf_get_addr(substream, ofs) + pt;
			c->dwSegPtrPhys = cpu_to_le32(addr);
			pt = (pt + f) % PAGE_SIZE;
			if (pt == 0)
				j++;
			c->dwSegLen = cpu_to_le32(f);
			c->dwStat_Ctl =
			    cpu_to_le32(IEOB_ENABLE | IEOS_ENABLE |
					IEOC_ENABLE);
			p = c;
			size -= f;
		}
		data->sgdbuf[i].dwSegLen = cpu_to_le32(size);
	}
	if (lbuspath && lbuspath != data->lbuspath) {
		if (data->lbuspath)
			freelbuspath(cif, data->source, data->lbuspath);
		alloclbuspath(cif, data->source, lbuspath,
			      &data->mixer, data->intdec);
		data->lbuspath = lbuspath;
		data->rate = 0;
	}
	if (data->rate != rate || data->format != format ||
	    data->channels != channels) {
		data->rate = rate;
		data->format = format;
		data->channels = channels;
		if (setsampleformat
		    (cif, data->mixer, data->id, channels, format)
		    || setsamplerate(cif, data->intdec, rate))
			err = -EIO;
	}
	spin_unlock_irq(&chip->lock);
	return err;
}