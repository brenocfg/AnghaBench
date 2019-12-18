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
struct snd_pcm {scalar_t__ private_data; } ;
struct rme32 {int /*<<< orphan*/ * spdif_pcm; } ;

/* Variables and functions */

__attribute__((used)) static void snd_rme32_free_spdif_pcm(struct snd_pcm *pcm)
{
	struct rme32 *rme32 = (struct rme32 *) pcm->private_data;
	rme32->spdif_pcm = NULL;
}