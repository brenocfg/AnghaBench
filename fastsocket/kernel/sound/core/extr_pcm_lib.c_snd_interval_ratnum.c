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
struct snd_ratnum {unsigned int num; unsigned int den_min; unsigned int den_max; unsigned int den_step; } ;
struct snd_interval {unsigned int min; int empty; int openmin; unsigned int max; int openmax; scalar_t__ integer; } ;

/* Variables and functions */
 int EINVAL ; 
 void* div_down (unsigned int,unsigned int) ; 
 void* div_up (unsigned int,unsigned int) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 scalar_t__ snd_interval_single (struct snd_interval*) ; 

int snd_interval_ratnum(struct snd_interval *i,
			unsigned int rats_count, struct snd_ratnum *rats,
			unsigned int *nump, unsigned int *denp)
{
	unsigned int best_num, best_den;
	int best_diff;
	unsigned int k;
	struct snd_interval t;
	int err;
	unsigned int result_num, result_den;
	int result_diff;

	best_num = best_den = best_diff = 0;
	for (k = 0; k < rats_count; ++k) {
		unsigned int num = rats[k].num;
		unsigned int den;
		unsigned int q = i->min;
		int diff;
		if (q == 0)
			q = 1;
		den = div_up(num, q);
		if (den < rats[k].den_min)
			continue;
		if (den > rats[k].den_max)
			den = rats[k].den_max;
		else {
			unsigned int r;
			r = (den - rats[k].den_min) % rats[k].den_step;
			if (r != 0)
				den -= r;
		}
		diff = num - q * den;
		if (diff < 0)
			diff = -diff;
		if (best_num == 0 ||
		    diff * best_den < best_diff * den) {
			best_diff = diff;
			best_den = den;
			best_num = num;
		}
	}
	if (best_den == 0) {
		i->empty = 1;
		return -EINVAL;
	}
	t.min = div_down(best_num, best_den);
	t.openmin = !!(best_num % best_den);
	
	result_num = best_num;
	result_diff = best_diff;
	result_den = best_den;
	best_num = best_den = best_diff = 0;
	for (k = 0; k < rats_count; ++k) {
		unsigned int num = rats[k].num;
		unsigned int den;
		unsigned int q = i->max;
		int diff;
		if (q == 0) {
			i->empty = 1;
			return -EINVAL;
		}
		den = div_down(num, q);
		if (den > rats[k].den_max)
			continue;
		if (den < rats[k].den_min)
			den = rats[k].den_min;
		else {
			unsigned int r;
			r = (den - rats[k].den_min) % rats[k].den_step;
			if (r != 0)
				den += rats[k].den_step - r;
		}
		diff = q * den - num;
		if (diff < 0)
			diff = -diff;
		if (best_num == 0 ||
		    diff * best_den < best_diff * den) {
			best_diff = diff;
			best_den = den;
			best_num = num;
		}
	}
	if (best_den == 0) {
		i->empty = 1;
		return -EINVAL;
	}
	t.max = div_up(best_num, best_den);
	t.openmax = !!(best_num % best_den);
	t.integer = 0;
	err = snd_interval_refine(i, &t);
	if (err < 0)
		return err;

	if (snd_interval_single(i)) {
		if (best_diff * result_den < result_diff * best_den) {
			result_num = best_num;
			result_den = best_den;
		}
		if (nump)
			*nump = result_num;
		if (denp)
			*denp = result_den;
	}
	return err;
}