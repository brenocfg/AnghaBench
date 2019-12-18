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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 double MIN_TEXT_SIZE ; 
 double SLOT_HEIGHT ; 
 double SLOT_MULT ; 
 double cpu2y (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 double round_text_size (double) ; 
 int /*<<< orphan*/  svgfile ; 
 double time2pixels (int /*<<< orphan*/ ) ; 

void svg_process(int cpu, u64 start, u64 end, const char *type, const char *name)
{
	double width;

	if (!svgfile)
		return;


	fprintf(svgfile, "<g transform=\"translate(%4.8f,%4.8f)\">\n", time2pixels(start), cpu2y(cpu));
	fprintf(svgfile, "<rect x=\"0\" width=\"%4.8f\" y=\"0\" height=\"%4.1f\" class=\"%s\"/>\n",
		time2pixels(end)-time2pixels(start), SLOT_MULT+SLOT_HEIGHT, type);
	width = time2pixels(end)-time2pixels(start);
	if (width > 6)
		width = 6;

	width = round_text_size(width);

	if (width > MIN_TEXT_SIZE)
		fprintf(svgfile, "<text transform=\"rotate(90)\" font-size=\"%3.8fpt\">%s</text>\n",
			width, name);

	fprintf(svgfile, "</g>\n");
}