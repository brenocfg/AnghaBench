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
struct snd_ac97 {int id; } ;
struct ac97_codec_id {int id; int mask; char const* name; } ;

/* Variables and functions */
 struct ac97_codec_id* snd_ac97_codec_ids ; 

const char *snd_ac97_get_short_name(struct snd_ac97 *ac97)
{
	const struct ac97_codec_id *pid;

	for (pid = snd_ac97_codec_ids; pid->id; pid++)
		if (pid->id == (ac97->id & pid->mask))
			return pid->name;
	return "unknown codec";
}