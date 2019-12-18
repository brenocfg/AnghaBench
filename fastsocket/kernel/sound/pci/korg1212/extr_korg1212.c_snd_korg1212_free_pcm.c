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
struct snd_pcm {struct snd_korg1212* private_data; } ;
struct snd_korg1212 {size_t cardState; int /*<<< orphan*/ * pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static void snd_korg1212_free_pcm(struct snd_pcm *pcm)
{
        struct snd_korg1212 *korg1212 = pcm->private_data;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_free_pcm [%s]\n",
			   stateName[korg1212->cardState]);

        korg1212->pcm = NULL;
}