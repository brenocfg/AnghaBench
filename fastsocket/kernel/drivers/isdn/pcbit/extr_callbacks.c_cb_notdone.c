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
struct pcbit_dev {int dummy; } ;
struct pcbit_chan {int dummy; } ;
struct callb_data {int dummy; } ;

/* Variables and functions */

void cb_notdone(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		struct callb_data *data)
{
}