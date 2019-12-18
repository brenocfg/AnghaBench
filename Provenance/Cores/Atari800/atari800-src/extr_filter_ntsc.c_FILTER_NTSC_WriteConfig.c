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
struct TYPE_2__ {double sharpness; double resolution; double artifacts; double fringing; double bleed; double burst_phase; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ FILTER_NTSC_setup ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,double) ; 

void FILTER_NTSC_WriteConfig(FILE *fp)
{
	fprintf(fp, "FILTER_NTSC_SHARPNESS=%g\n", FILTER_NTSC_setup.sharpness);
	fprintf(fp, "FILTER_NTSC_RESOLUTION=%g\n", FILTER_NTSC_setup.resolution);
	fprintf(fp, "FILTER_NTSC_ARTIFACTS=%g\n", FILTER_NTSC_setup.artifacts);
	fprintf(fp, "FILTER_NTSC_FRINGING=%g\n", FILTER_NTSC_setup.fringing);
	fprintf(fp, "FILTER_NTSC_BLEED=%g\n", FILTER_NTSC_setup.bleed);
	fprintf(fp, "FILTER_NTSC_BURST_PHASE=%g\n", FILTER_NTSC_setup.burst_phase);
}