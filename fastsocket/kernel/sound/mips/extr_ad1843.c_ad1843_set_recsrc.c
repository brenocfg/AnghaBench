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
struct snd_ad1843 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ad1843_LSS ; 
 int /*<<< orphan*/  ad1843_RSS ; 
 int /*<<< orphan*/  ad1843_write_multi (struct snd_ad1843*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

int ad1843_set_recsrc(struct snd_ad1843 *ad1843, int newsrc)
{
	if (newsrc < 0 || newsrc > 2)
		return -EINVAL;

	ad1843_write_multi(ad1843, 2, &ad1843_LSS, newsrc, &ad1843_RSS, newsrc);
	return newsrc;
}