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
struct hda_codec_preset_list {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hda_preset_tables ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preset_mutex ; 

int snd_hda_add_codec_preset(struct hda_codec_preset_list *preset)
{
	mutex_lock(&preset_mutex);
	list_add_tail(&preset->list, &hda_preset_tables);
	mutex_unlock(&preset_mutex);
	return 0;
}