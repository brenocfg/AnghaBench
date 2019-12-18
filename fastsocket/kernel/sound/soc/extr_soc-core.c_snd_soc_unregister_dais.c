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
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_unregister_dai (struct snd_soc_dai*) ; 

void snd_soc_unregister_dais(struct snd_soc_dai *dai, size_t count)
{
	int i;

	for (i = 0; i < count; i++)
		snd_soc_unregister_dai(&dai[i]);
}