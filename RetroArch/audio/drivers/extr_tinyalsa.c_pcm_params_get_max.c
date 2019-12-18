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
struct snd_pcm_hw_params {int dummy; } ;
struct pcm_params {int dummy; } ;
typedef  enum pcm_param { ____Placeholder_pcm_param } pcm_param ;

/* Variables and functions */
 unsigned int param_get_max (struct snd_pcm_hw_params const*,int) ; 
 int pcm_param_to_alsa (int) ; 

__attribute__((used)) static unsigned int pcm_params_get_max(const struct pcm_params *pcm_params,
      enum pcm_param param)
{
   const struct snd_pcm_hw_params *params = (const struct snd_pcm_hw_params *)pcm_params;
   int p;

   if (!params)
      return 0;

   p = pcm_param_to_alsa(param);
   if (p < 0)
      return 0;

   return param_get_max(params, p);
}