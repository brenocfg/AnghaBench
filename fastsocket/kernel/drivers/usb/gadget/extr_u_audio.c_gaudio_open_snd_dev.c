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
struct snd_pcm_file {int /*<<< orphan*/ * substream; } ;
struct gaudio_snd_dev {struct gaudio* card; int /*<<< orphan*/ * substream; TYPE_1__* filp; } ;
struct gaudio {struct gaudio_snd_dev capture; struct gaudio_snd_dev playback; struct gaudio_snd_dev control; } ;
struct TYPE_3__ {struct snd_pcm_file* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ERROR (struct gaudio*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int PTR_ERR (TYPE_1__*) ; 
 void* filp_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fn_cap ; 
 int /*<<< orphan*/  fn_cntl ; 
 int /*<<< orphan*/  fn_play ; 
 int /*<<< orphan*/  playback_default_hw_params (struct gaudio_snd_dev*) ; 

__attribute__((used)) static int gaudio_open_snd_dev(struct gaudio *card)
{
	struct snd_pcm_file *pcm_file;
	struct gaudio_snd_dev *snd;

	if (!card)
		return -ENODEV;

	/* Open control device */
	snd = &card->control;
	snd->filp = filp_open(fn_cntl, O_RDWR, 0);
	if (IS_ERR(snd->filp)) {
		int ret = PTR_ERR(snd->filp);
		ERROR(card, "unable to open sound control device file: %s\n",
				fn_cntl);
		snd->filp = NULL;
		return ret;
	}
	snd->card = card;

	/* Open PCM playback device and setup substream */
	snd = &card->playback;
	snd->filp = filp_open(fn_play, O_WRONLY, 0);
	if (IS_ERR(snd->filp)) {
		ERROR(card, "No such PCM playback device: %s\n", fn_play);
		snd->filp = NULL;
	}
	pcm_file = snd->filp->private_data;
	snd->substream = pcm_file->substream;
	snd->card = card;
	playback_default_hw_params(snd);

	/* Open PCM capture device and setup substream */
	snd = &card->capture;
	snd->filp = filp_open(fn_cap, O_RDONLY, 0);
	if (IS_ERR(snd->filp)) {
		ERROR(card, "No such PCM capture device: %s\n", fn_cap);
		snd->substream = NULL;
		snd->card = NULL;
	} else {
		pcm_file = snd->filp->private_data;
		snd->substream = pcm_file->substream;
		snd->card = card;
	}

	return 0;
}