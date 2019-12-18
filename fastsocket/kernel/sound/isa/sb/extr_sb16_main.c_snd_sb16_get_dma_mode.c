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
struct snd_sb {scalar_t__ dma8; scalar_t__ dma16; int force_mode16; } ;

/* Variables and functions */
#define  SB_MODE_CAPTURE_16 129 
#define  SB_MODE_PLAYBACK_16 128 

__attribute__((used)) static int snd_sb16_get_dma_mode(struct snd_sb *chip)
{
	if (chip->dma8 < 0 || chip->dma16 < 0)
		return 0;
	switch (chip->force_mode16) {
	case SB_MODE_PLAYBACK_16:
		return 1;
	case SB_MODE_CAPTURE_16:
		return 2;
	default:
		return 0;
	}
}