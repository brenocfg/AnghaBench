#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int con_xres; int /*<<< orphan*/  background; scalar_t__ destbuffer; } ;
typedef  TYPE_1__ console_data_s ;

/* Variables and functions */
 int FONT_XSIZE ; 
 unsigned int FONT_YSIZE ; 
 TYPE_1__* curr_con ; 

__attribute__((used)) static void __console_clear_line( int line, int from, int to ) {
	console_data_s *con;
	unsigned int c;
	unsigned int *p;
	unsigned int x_pixels;
	unsigned int px_per_col = FONT_XSIZE/2;
	unsigned int line_height = FONT_YSIZE;
	unsigned int line_width;

	if( !(con = curr_con) ) return;
	// For some reason there are xres/2 pixels per screen width
  x_pixels = con->con_xres / 2;

	line_width = (to - from)*px_per_col;
	p = (unsigned int*)con->destbuffer;

	// Move pointer to the current line and column offset
	p += line*(FONT_YSIZE*x_pixels) + from*px_per_col;

	// Clears 1 line of pixels at a time, line_height times
  while( line_height-- ) {
  	c = line_width;
    while( c-- )
      *p++ = con->background;
    p -= line_width;
    p += x_pixels;
  }
}