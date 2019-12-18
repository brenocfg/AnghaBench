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
struct snd_soc_dapm_widget {int connected; int /*<<< orphan*/  list; int /*<<< orphan*/  sinks; int /*<<< orphan*/  sources; struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int /*<<< orphan*/  dapm_widgets; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct snd_soc_dapm_widget* dapm_cnew_widget (struct snd_soc_dapm_widget const*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int snd_soc_dapm_new_control(struct snd_soc_codec *codec,
	const struct snd_soc_dapm_widget *widget)
{
	struct snd_soc_dapm_widget *w;

	if ((w = dapm_cnew_widget(widget)) == NULL)
		return -ENOMEM;

	w->codec = codec;
	INIT_LIST_HEAD(&w->sources);
	INIT_LIST_HEAD(&w->sinks);
	INIT_LIST_HEAD(&w->list);
	list_add(&w->list, &codec->dapm_widgets);

	/* machine layer set ups unconnected pins and insertions */
	w->connected = 1;
	return 0;
}