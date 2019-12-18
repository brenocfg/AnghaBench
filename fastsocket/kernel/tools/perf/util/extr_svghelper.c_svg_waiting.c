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
typedef  int u64 ;

/* Variables and functions */
 double MIN_TEXT_SIZE ; 
 double SLOT_HEIGHT ; 
 int SLOT_MULT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 double round_text_size (double) ; 
 int /*<<< orphan*/  svgfile ; 
 double time2pixels (int) ; 
 char* time_to_string (int) ; 

void svg_waiting(int Yslot, u64 start, u64 end)
{
	char *text;
	const char *style;
	double font_size;

	if (!svgfile)
		return;

	style = "waiting";

	if (end-start > 10 * 1000000) /* 10 msec */
		style = "WAITING";

	text = time_to_string(end-start);

	font_size = 1.0 * (time2pixels(end)-time2pixels(start));

	if (font_size > 3)
		font_size = 3;

	font_size = round_text_size(font_size);

	fprintf(svgfile, "<g transform=\"translate(%4.8f,%4.8f)\">\n", time2pixels(start), Yslot * SLOT_MULT);
	fprintf(svgfile, "<rect x=\"0\" width=\"%4.8f\" y=\"0\" height=\"%4.1f\" class=\"%s\"/>\n",
		time2pixels(end)-time2pixels(start), SLOT_HEIGHT, style);
	if (font_size > MIN_TEXT_SIZE)
		fprintf(svgfile, "<text transform=\"rotate(90)\" font-size=\"%1.8fpt\"> %s</text>\n",
			font_size, text);
	fprintf(svgfile, "</g>\n");
}