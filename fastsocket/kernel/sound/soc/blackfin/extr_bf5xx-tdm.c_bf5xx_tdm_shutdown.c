#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {scalar_t__ configured; } ;

/* Variables and functions */
 TYPE_1__ bf5xx_tdm ; 

__attribute__((used)) static void bf5xx_tdm_shutdown(struct snd_pcm_substream *substream,
	struct snd_soc_dai *dai)
{
	/* No active stream, SPORT is allowed to be configured again. */
	if (!dai->active)
		bf5xx_tdm.configured = 0;
}