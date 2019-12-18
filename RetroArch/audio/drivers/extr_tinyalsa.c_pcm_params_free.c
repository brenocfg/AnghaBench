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

/* Variables and functions */
 int /*<<< orphan*/  free (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static void pcm_params_free(struct pcm_params *pcm_params)
{
   struct snd_pcm_hw_params *params = (struct snd_pcm_hw_params *)pcm_params;

   if (params)
      free(params);
}