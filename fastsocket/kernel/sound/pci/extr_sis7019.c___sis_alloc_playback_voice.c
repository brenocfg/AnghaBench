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
struct voice {int flags; } ;
struct sis7019 {struct voice* voices; } ;

/* Variables and functions */
 int VOICE_IN_USE ; 

__attribute__((used)) static struct voice *__sis_alloc_playback_voice(struct sis7019 *sis)
{
	/* Must hold the voice_lock on entry */
	struct voice *voice;
	int i;

	for (i = 0; i < 64; i++) {
		voice = &sis->voices[i];
		if (voice->flags & VOICE_IN_USE)
			continue;
		voice->flags |= VOICE_IN_USE;
		goto found_one;
	}
	voice = NULL;

found_one:
	return voice;
}