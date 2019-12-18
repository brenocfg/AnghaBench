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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 double NSEC_PER_MSEC ; 
 int /*<<< orphan*/  PERF_COLOR_NORMAL ; 
 int /*<<< orphan*/  PERF_COLOR_RED ; 
 int /*<<< orphan*/  PERF_COLOR_YELLOW ; 
 scalar_t__ color_fprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,double) ; 
 size_t fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static size_t fprintf_duration(unsigned long t, FILE *fp)
{
	double duration = (double)t / NSEC_PER_MSEC;
	size_t printed = fprintf(fp, "(");

	if (duration >= 1.0)
		printed += color_fprintf(fp, PERF_COLOR_RED, "%6.3f ms", duration);
	else if (duration >= 0.01)
		printed += color_fprintf(fp, PERF_COLOR_YELLOW, "%6.3f ms", duration);
	else
		printed += color_fprintf(fp, PERF_COLOR_NORMAL, "%6.3f ms", duration);
	return printed + fprintf(stdout, "): ");
}