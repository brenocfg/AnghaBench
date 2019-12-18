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
struct hdsp {int use_midi_tasklet; } ;

/* Variables and functions */

__attribute__((used)) static int hdsp_set_use_midi_tasklet(struct hdsp *hdsp, int use_tasklet)
{
	if (use_tasklet)
		hdsp->use_midi_tasklet = 1;
	else
		hdsp->use_midi_tasklet = 0;
	return 0;
}