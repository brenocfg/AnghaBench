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
struct snd_soc_dapm_widget {int num_kcontrols; TYPE_1__* kcontrols; int /*<<< orphan*/  sinks; int /*<<< orphan*/  sources; } ;
struct snd_soc_dapm_path {int /*<<< orphan*/  name; int /*<<< orphan*/  list_source; int /*<<< orphan*/  list_sink; int /*<<< orphan*/  list; } ;
struct snd_soc_codec {int /*<<< orphan*/  dapm_paths; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dapm_set_path_status (struct snd_soc_dapm_widget*,struct snd_soc_dapm_path*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dapm_connect_mixer(struct snd_soc_codec *codec,
	struct snd_soc_dapm_widget *src, struct snd_soc_dapm_widget *dest,
	struct snd_soc_dapm_path *path, const char *control_name)
{
	int i;

	/* search for mixer kcontrol */
	for (i = 0; i < dest->num_kcontrols; i++) {
		if (!strcmp(control_name, dest->kcontrols[i].name)) {
			list_add(&path->list, &codec->dapm_paths);
			list_add(&path->list_sink, &dest->sources);
			list_add(&path->list_source, &src->sinks);
			path->name = dest->kcontrols[i].name;
			dapm_set_path_status(dest, path, i);
			return 0;
		}
	}
	return -ENODEV;
}