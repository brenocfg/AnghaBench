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
struct hdsp {int system_sample_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdsp_set_dds_value (struct hdsp*,int) ; 

__attribute__((used)) static int hdsp_set_dds_offset(struct hdsp *hdsp, int offset_hz)
{
	int rate = hdsp->system_sample_rate + offset_hz;
	hdsp_set_dds_value(hdsp, rate);
	return 0;
}