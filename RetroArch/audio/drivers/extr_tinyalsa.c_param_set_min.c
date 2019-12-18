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
struct snd_interval {unsigned int min; } ;

/* Variables and functions */
 scalar_t__ param_is_interval (int) ; 
 struct snd_interval* param_to_interval (struct snd_pcm_hw_params*,int) ; 

__attribute__((used)) static void param_set_min(struct snd_pcm_hw_params *p, int n, unsigned int val)
{
    if (param_is_interval(n))
    {
        struct snd_interval *i = param_to_interval(p, n);
        i->min = val;
    }
}