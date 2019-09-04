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
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  glReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int height ; 
 unsigned char* malloc (int) ; 
 int width ; 

void Verify() {
  unsigned char *data = malloc(width*height*4 + 16);
  int *last = (int*)(data + width*height*4 - 4);
  int *after = (int*)(data + width*height*4);
  *last = 0xdeadbeef;
  *after = 0x12345678;
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
  assert(*last != 0xdeadbeef); // should overwrite the buffer to the end
  assert(*after == 0x12345678); // nothing should be written afterwards!
  // Should see some blue, and nothing else
  int seen = 0;
  int ok = 1;
  for (int x = 0; x < width*height; x++) {
    seen = seen || data[x*4+2] != 0;
    ok = ok && (data[x*4+0] == 0);
    ok = ok && (data[x*4+1] == 0);
  }
  int result = seen && ok;
  REPORT_RESULT(result);
}