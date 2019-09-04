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

/* Variables and functions */
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  glReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ malloc (int) ; 

void verify() {
  int width = 640, height = 480;
  unsigned char *data = (unsigned char*)malloc(width*height*4);
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
  int sum = 0;
  for (int x = 0; x < width*height*4; x++) {
    if (x % 4 != 3) sum += x * data[x];
  }
#ifdef __EMSCRIPTEN__
  REPORT_RESULT(sum);
#endif
}