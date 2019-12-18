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
struct hda_gen_spec {int /*<<< orphan*/  loopback_list; int /*<<< orphan*/  paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_kctls (struct hda_gen_spec*) ; 
 int /*<<< orphan*/  snd_array_free (int /*<<< orphan*/ *) ; 

void snd_hda_gen_spec_free(struct hda_gen_spec *spec)
{
	if (!spec)
		return;
	free_kctls(spec);
	snd_array_free(&spec->paths);
	snd_array_free(&spec->loopback_list);
}