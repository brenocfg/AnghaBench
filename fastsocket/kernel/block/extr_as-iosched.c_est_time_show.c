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
struct elevator_queue {struct as_data* elevator_data; } ;
struct as_data {int exit_prob; int exit_no_coop; unsigned long long new_ttime_mean; scalar_t__ new_seek_mean; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t est_time_show(struct elevator_queue *e, char *page)
{
	struct as_data *ad = e->elevator_data;
	int pos = 0;

	pos += sprintf(page+pos, "%lu %% exit probability\n",
				100*ad->exit_prob/256);
	pos += sprintf(page+pos, "%lu %% probability of exiting without a "
				"cooperating process submitting IO\n",
				100*ad->exit_no_coop/256);
	pos += sprintf(page+pos, "%lu ms new thinktime\n", ad->new_ttime_mean);
	pos += sprintf(page+pos, "%llu sectors new seek distance\n",
				(unsigned long long)ad->new_seek_mean);

	return pos;
}