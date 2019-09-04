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
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  emscripten_get_canvas_element_size (char*,int*,int*) ; 
 int /*<<< orphan*/  emscripten_get_element_css_size (int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  printf (char*,int,int,double,double) ; 

EM_BOOL on_canvassize_changed(int eventType, const void *reserved, void *userData)
{
  int w, h;
  emscripten_get_canvas_element_size("#canvas", &w, &h);
  double cssW, cssH;
  emscripten_get_element_css_size(0, &cssW, &cssH);
  printf("Canvas resized: WebGL RTT size: %dx%d, canvas CSS size: %02gx%02g\n", w, h, cssW, cssH);
  return 0;
}