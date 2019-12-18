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
struct ac97_frame {int /*<<< orphan*/  ac97_pcm_r; int /*<<< orphan*/  ac97_pcm_l; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */

void bf5xx_ac97_to_pcm(const struct ac97_frame *src, __u16 *dst,
		size_t count)
{
	while (count--) {
		*(dst++) = src->ac97_pcm_l;
		*(dst++) = src->ac97_pcm_r;
		src++;
	}
}