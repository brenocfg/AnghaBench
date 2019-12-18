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
struct TYPE_2__ {char* label; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MC_LABEL_LEN ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t channel_dimm_label_show(struct csrow_info *csrow,
				char *data, int channel)
{
	/* if field has not been initialized, there is nothing to send */
	if (!csrow->channels[channel].label[0])
		return 0;

	return snprintf(data, EDAC_MC_LABEL_LEN, "%s\n",
			csrow->channels[channel].label);
}