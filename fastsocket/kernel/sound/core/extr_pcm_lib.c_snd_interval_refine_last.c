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
struct snd_interval {int /*<<< orphan*/  min; scalar_t__ openmin; scalar_t__ openmax; int /*<<< orphan*/  max; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_interval_empty (struct snd_interval*) ; 
 scalar_t__ snd_interval_single (struct snd_interval*) ; 

__attribute__((used)) static int snd_interval_refine_last(struct snd_interval *i)
{
	if (snd_BUG_ON(snd_interval_empty(i)))
		return -EINVAL;
	if (snd_interval_single(i))
		return 0;
	i->min = i->max;
	i->openmin = i->openmax;
	if (i->openmin)
		i->min--;
	return 1;
}