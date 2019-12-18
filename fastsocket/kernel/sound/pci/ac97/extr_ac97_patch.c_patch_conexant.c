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
struct snd_ac97 {int /*<<< orphan*/ * rates; int /*<<< orphan*/  ext_id; int /*<<< orphan*/  flags; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CX_SPDIF ; 
 int /*<<< orphan*/  AC97_EI_SPDIF ; 
 size_t AC97_RATES_SPDIF ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_48000 ; 
 int /*<<< orphan*/  patch_conexant_ops ; 

__attribute__((used)) static int patch_conexant(struct snd_ac97 * ac97)
{
	ac97->build_ops = &patch_conexant_ops;
	ac97->flags |= AC97_CX_SPDIF;
        ac97->ext_id |= AC97_EI_SPDIF;	/* force the detection of spdif */
	ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */
	return 0;
}