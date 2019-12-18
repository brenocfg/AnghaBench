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

/* Variables and functions */

__attribute__((used)) static inline int snd_cs4235_mixer_output_accu_get_volume(int vol)
{
	switch ((vol >> 5) & 3) {
	case 0: return 1;
	case 1: return 3;
	case 2: return 2;
	case 3: return 0;
 	}
	return 3;
}