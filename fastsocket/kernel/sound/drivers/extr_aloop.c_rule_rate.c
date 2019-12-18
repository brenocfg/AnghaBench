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
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct snd_pcm_hardware* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_pcm_hardware {int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; } ;
struct snd_interval {scalar_t__ integer; scalar_t__ openmax; scalar_t__ openmin; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (int /*<<< orphan*/ ,struct snd_interval*) ; 

__attribute__((used)) static int rule_rate(struct snd_pcm_hw_params *params,
		     struct snd_pcm_hw_rule *rule)
{
	struct snd_pcm_hardware *hw = rule->private;
	struct snd_interval t;

        t.min = hw->rate_min;
        t.max = hw->rate_max;
        t.openmin = t.openmax = 0;
        t.integer = 0;
	return snd_interval_refine(hw_param_interval(params, rule->var), &t);
}