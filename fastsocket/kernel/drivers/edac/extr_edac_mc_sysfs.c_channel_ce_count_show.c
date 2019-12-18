#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct csrow_info {TYPE_1__* channels; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int ce_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t channel_ce_count_show(struct csrow_info *csrow,
				char *data, int channel)
{
	return sprintf(data, "%u\n", csrow->channels[channel].ce_count);
}