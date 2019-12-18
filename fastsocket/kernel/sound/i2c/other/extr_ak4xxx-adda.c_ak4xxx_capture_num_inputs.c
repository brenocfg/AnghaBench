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
struct snd_akm4xxx {TYPE_1__* adc_info; } ;
struct TYPE_2__ {char** input_names; } ;

/* Variables and functions */
 int AK5365_NUM_INPUTS ; 

__attribute__((used)) static int ak4xxx_capture_num_inputs(struct snd_akm4xxx *ak, int mixer_ch)
{
	int num_names;
	const char **input_names;

	input_names = ak->adc_info[mixer_ch].input_names;
	num_names = 0;
	while (num_names < AK5365_NUM_INPUTS && input_names[num_names])
		++num_names;
	return num_names;
}