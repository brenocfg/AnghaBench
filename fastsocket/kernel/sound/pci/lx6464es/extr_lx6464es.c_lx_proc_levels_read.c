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
typedef  int /*<<< orphan*/  u32 ;
struct snd_info_entry {struct lx6464es* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct lx6464es {int dummy; } ;

/* Variables and functions */
 int lx_level_peaks (struct lx6464es*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void lx_proc_levels_read(struct snd_info_entry *entry,
				struct snd_info_buffer *buffer)
{
	u32 levels[64];
	int err;
	int i, j;
	struct lx6464es *chip = entry->private_data;

	snd_iprintf(buffer, "capture levels:\n");
	err = lx_level_peaks(chip, 1, 64, levels);
	if (err < 0)
		return;

	for (i = 0; i != 8; ++i) {
		for (j = 0; j != 8; ++j)
			snd_iprintf(buffer, "%08x ", levels[i*8+j]);
		snd_iprintf(buffer, "\n");
	}

	snd_iprintf(buffer, "\nplayback levels:\n");

	err = lx_level_peaks(chip, 0, 64, levels);
	if (err < 0)
		return;

	for (i = 0; i != 8; ++i) {
		for (j = 0; j != 8; ++j)
			snd_iprintf(buffer, "%08x ", levels[i*8+j]);
		snd_iprintf(buffer, "\n");
	}

	snd_iprintf(buffer, "\n");
}