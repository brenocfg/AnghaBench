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
struct snd_pcm_hw_params {unsigned int rmask; unsigned int info; scalar_t__ cmask; } ;
struct snd_mask {int /*<<< orphan*/ * bits; } ;
struct snd_interval {int /*<<< orphan*/  max; scalar_t__ min; } ;

/* Variables and functions */
 int SNDRV_PCM_HW_PARAM_FIRST_INTERVAL ; 
 int SNDRV_PCM_HW_PARAM_FIRST_MASK ; 
 int SNDRV_PCM_HW_PARAM_LAST_INTERVAL ; 
 int SNDRV_PCM_HW_PARAM_LAST_MASK ; 
 int /*<<< orphan*/  memset (struct snd_pcm_hw_params*,int /*<<< orphan*/ ,int) ; 
 struct snd_interval* param_to_interval (struct snd_pcm_hw_params*,int) ; 
 struct snd_mask* param_to_mask (struct snd_pcm_hw_params*,int) ; 

__attribute__((used)) static void param_init(struct snd_pcm_hw_params *p)
{
   int n;

   memset(p, 0, sizeof(*p));
   for (n = SNDRV_PCM_HW_PARAM_FIRST_MASK;
         n <= SNDRV_PCM_HW_PARAM_LAST_MASK; n++)
   {
      struct snd_mask *m = param_to_mask(p, n);
      m->bits[0] = ~0;
      m->bits[1] = ~0;
   }
   for (n = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL;
         n <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; n++)
   {
      struct snd_interval *i = param_to_interval(p, n);
      i->min = 0;
      i->max = ~0;
   }
   p->rmask = ~0U;
   p->cmask = 0;
   p->info = ~0U;
}