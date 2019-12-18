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
struct snd_pcm_hw_params {int cmask; int rmask; } ;
struct snd_mask {int dummy; } ;
struct snd_interval {int openmin; int openmax; unsigned int min; unsigned int max; scalar_t__ integer; scalar_t__ empty; } ;
typedef  int snd_pcm_hw_param_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ hw_is_interval (int) ; 
 scalar_t__ hw_is_mask (int) ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int) ; 
 int /*<<< orphan*/  snd_interval_none (struct snd_interval*) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 int snd_interval_refine_set (struct snd_interval*,unsigned int) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 int snd_mask_refine_set (struct snd_mask*,unsigned int) ; 

__attribute__((used)) static int _snd_pcm_hw_param_set(struct snd_pcm_hw_params *params,
				 snd_pcm_hw_param_t var, unsigned int val,
				 int dir)
{
	int changed;
	if (hw_is_mask(var)) {
		struct snd_mask *m = hw_param_mask(params, var);
		if (val == 0 && dir < 0) {
			changed = -EINVAL;
			snd_mask_none(m);
		} else {
			if (dir > 0)
				val++;
			else if (dir < 0)
				val--;
			changed = snd_mask_refine_set(hw_param_mask(params, var), val);
		}
	} else if (hw_is_interval(var)) {
		struct snd_interval *i = hw_param_interval(params, var);
		if (val == 0 && dir < 0) {
			changed = -EINVAL;
			snd_interval_none(i);
		} else if (dir == 0)
			changed = snd_interval_refine_set(i, val);
		else {
			struct snd_interval t;
			t.openmin = 1;
			t.openmax = 1;
			t.empty = 0;
			t.integer = 0;
			if (dir < 0) {
				t.min = val - 1;
				t.max = val;
			} else {
				t.min = val;
				t.max = val+1;
			}
			changed = snd_interval_refine(i, &t);
		}
	} else
		return -EINVAL;
	if (changed) {
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	}
	return changed;
}