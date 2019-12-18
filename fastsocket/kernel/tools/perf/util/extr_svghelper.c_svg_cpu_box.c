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
typedef  void* u64 ;

/* Variables and functions */
 int SLOT_HEIGHT ; 
 double SLOT_MULT ; 
 double cpu2y (int) ; 
 char* cpu_model () ; 
 int /*<<< orphan*/  first_time ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,double,...) ; 
 int /*<<< orphan*/  last_time ; 
 void* max_freq ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  svgfile ; 
 double time2pixels (int /*<<< orphan*/ ) ; 
 void* turbo_frequency ; 

void svg_cpu_box(int cpu, u64 __max_freq, u64 __turbo_freq)
{
	char cpu_string[80];
	if (!svgfile)
		return;

	max_freq = __max_freq;
	turbo_frequency = __turbo_freq;

	fprintf(svgfile, "<rect x=\"%4.8f\" width=\"%4.8f\" y=\"%4.1f\" height=\"%4.1f\" class=\"cpu\"/>\n",
		time2pixels(first_time),
		time2pixels(last_time)-time2pixels(first_time),
		cpu2y(cpu), SLOT_MULT+SLOT_HEIGHT);

	sprintf(cpu_string, "CPU %i", (int)cpu+1);
	fprintf(svgfile, "<text x=\"%4.8f\" y=\"%4.8f\">%s</text>\n",
		10+time2pixels(first_time), cpu2y(cpu) + SLOT_HEIGHT/2, cpu_string);

	fprintf(svgfile, "<text transform=\"translate(%4.8f,%4.8f)\" font-size=\"1.25pt\">%s</text>\n",
		10+time2pixels(first_time), cpu2y(cpu) + SLOT_MULT + SLOT_HEIGHT - 4, cpu_model());
}