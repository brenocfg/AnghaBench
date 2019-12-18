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
struct snd_ac97 {int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AD_MISC ; 
 int /*<<< orphan*/  patch_ad1881 (struct snd_ac97*) ; 
 int /*<<< orphan*/  patch_ad1885_build_ops ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int patch_ad1885(struct snd_ac97 * ac97)
{
	patch_ad1881(ac97);
	/* This is required to deal with the Intel D815EEAL2 */
	/* i.e. Line out is actually headphone out from codec */

	/* set default */
	snd_ac97_write_cache(ac97, AC97_AD_MISC, 0x0404);

	ac97->build_ops = &patch_ad1885_build_ops;
	return 0;
}