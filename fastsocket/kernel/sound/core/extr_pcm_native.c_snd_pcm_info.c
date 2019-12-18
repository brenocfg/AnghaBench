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
struct snd_pcm_substream {TYPE_2__* ops; struct snd_pcm_runtime* runtime; int /*<<< orphan*/  name; int /*<<< orphan*/  number; int /*<<< orphan*/  stream; struct snd_pcm_str* pstr; struct snd_pcm* pcm; } ;
struct snd_pcm_str {scalar_t__ substream_opened; scalar_t__ substream_count; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  sync; } ;
struct snd_pcm_info {int /*<<< orphan*/  sync; int /*<<< orphan*/  subname; scalar_t__ subdevices_avail; scalar_t__ subdevices_count; int /*<<< orphan*/  dev_subclass; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  stream; int /*<<< orphan*/  device; int /*<<< orphan*/  card; } ;
struct snd_pcm {int /*<<< orphan*/  dev_subclass; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  device; TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ioctl ) (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct snd_pcm_info*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_IOCTL1_INFO ; 
 int /*<<< orphan*/  memset (struct snd_pcm_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct snd_pcm_info*) ; 

int snd_pcm_info(struct snd_pcm_substream *substream, struct snd_pcm_info *info)
{
	struct snd_pcm_runtime *runtime;
	struct snd_pcm *pcm = substream->pcm;
	struct snd_pcm_str *pstr = substream->pstr;

	memset(info, 0, sizeof(*info));
	info->card = pcm->card->number;
	info->device = pcm->device;
	info->stream = substream->stream;
	info->subdevice = substream->number;
	strlcpy(info->id, pcm->id, sizeof(info->id));
	strlcpy(info->name, pcm->name, sizeof(info->name));
	info->dev_class = pcm->dev_class;
	info->dev_subclass = pcm->dev_subclass;
	info->subdevices_count = pstr->substream_count;
	info->subdevices_avail = pstr->substream_count - pstr->substream_opened;
	strlcpy(info->subname, substream->name, sizeof(info->subname));
	runtime = substream->runtime;
	/* AB: FIXME!!! This is definitely nonsense */
	if (runtime) {
		info->sync = runtime->sync;
		substream->ops->ioctl(substream, SNDRV_PCM_IOCTL1_INFO, info);
	}
	return 0;
}