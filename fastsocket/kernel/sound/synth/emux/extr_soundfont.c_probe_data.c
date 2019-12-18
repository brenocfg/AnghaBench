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
struct snd_sf_list {scalar_t__ currsf; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ find_sample (scalar_t__,int) ; 

__attribute__((used)) static int
probe_data(struct snd_sf_list *sflist, int sample_id)
{
	/* patch must be opened */
	if (sflist->currsf) {
		/* search the specified sample by optarg */
		if (find_sample(sflist->currsf, sample_id))
			return 0;
	}
	return -EINVAL;
}