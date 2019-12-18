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
struct soc_enum {int max; scalar_t__* texts; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  sinks; int /*<<< orphan*/  sources; } ;
struct snd_soc_dapm_path {char* name; int /*<<< orphan*/  list_source; int /*<<< orphan*/  list_sink; int /*<<< orphan*/  list; } ;
struct snd_soc_codec {int /*<<< orphan*/  dapm_paths; } ;
struct snd_kcontrol_new {scalar_t__ private_value; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dapm_set_path_status (struct snd_soc_dapm_widget*,struct snd_soc_dapm_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int dapm_connect_mux(struct snd_soc_codec *codec,
	struct snd_soc_dapm_widget *src, struct snd_soc_dapm_widget *dest,
	struct snd_soc_dapm_path *path, const char *control_name,
	const struct snd_kcontrol_new *kcontrol)
{
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	int i;

	for (i = 0; i < e->max; i++) {
		if (!(strcmp(control_name, e->texts[i]))) {
			list_add(&path->list, &codec->dapm_paths);
			list_add(&path->list_sink, &dest->sources);
			list_add(&path->list_source, &src->sinks);
			path->name = (char*)e->texts[i];
			dapm_set_path_status(dest, path, 0);
			return 0;
		}
	}

	return -ENODEV;
}