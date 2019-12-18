#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_sf_callback {int /*<<< orphan*/  sample_reset; int /*<<< orphan*/  sample_free; int /*<<< orphan*/  sample_new; struct snd_emux* private_data; } ;
struct snd_emux_voice {int dummy; } ;
struct TYPE_2__ {scalar_t__ sample_reset; scalar_t__ sample_free; scalar_t__ sample_new; } ;
struct snd_emux {scalar_t__ max_voices; int /*<<< orphan*/ * sflist; int /*<<< orphan*/  memhdr; TYPE_1__ ops; int /*<<< orphan*/ * voices; int /*<<< orphan*/  name; struct snd_card* card; int /*<<< orphan*/  hw; } ;
struct snd_card {int dummy; } ;
typedef  int /*<<< orphan*/  sf_cb ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct snd_sf_callback*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sf_sample_free ; 
 int /*<<< orphan*/  sf_sample_new ; 
 int /*<<< orphan*/  sf_sample_reset ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_emux_init_hwdep (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_init_seq (struct snd_emux*,struct snd_card*,int) ; 
 int /*<<< orphan*/  snd_emux_init_seq_oss (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_init_virmidi (struct snd_emux*,struct snd_card*) ; 
 int /*<<< orphan*/  snd_emux_init_voices (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_proc_init (struct snd_emux*,struct snd_card*,int) ; 
 int /*<<< orphan*/ * snd_sf_new (struct snd_sf_callback*,int /*<<< orphan*/ ) ; 

int snd_emux_register(struct snd_emux *emu, struct snd_card *card, int index, char *name)
{
	int err;
	struct snd_sf_callback sf_cb;

	if (snd_BUG_ON(!emu->hw || emu->max_voices <= 0))
		return -EINVAL;
	if (snd_BUG_ON(!card || !name))
		return -EINVAL;

	emu->card = card;
	emu->name = kstrdup(name, GFP_KERNEL);
	emu->voices = kcalloc(emu->max_voices, sizeof(struct snd_emux_voice),
			      GFP_KERNEL);
	if (emu->voices == NULL)
		return -ENOMEM;

	/* create soundfont list */
	memset(&sf_cb, 0, sizeof(sf_cb));
	sf_cb.private_data = emu;
	if (emu->ops.sample_new)
		sf_cb.sample_new = sf_sample_new;
	if (emu->ops.sample_free)
		sf_cb.sample_free = sf_sample_free;
	if (emu->ops.sample_reset)
		sf_cb.sample_reset = sf_sample_reset;
	emu->sflist = snd_sf_new(&sf_cb, emu->memhdr);
	if (emu->sflist == NULL)
		return -ENOMEM;

	if ((err = snd_emux_init_hwdep(emu)) < 0)
		return err;

	snd_emux_init_voices(emu);

	snd_emux_init_seq(emu, card, index);
#ifdef CONFIG_SND_SEQUENCER_OSS
	snd_emux_init_seq_oss(emu);
#endif
	snd_emux_init_virmidi(emu, card);

#ifdef CONFIG_PROC_FS
	snd_emux_proc_init(emu, card, index);
#endif
	return 0;
}