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
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 float cosf (float) ; 
 int /*<<< orphan*/  emscripten_get_canvas_element_size (char*,int*,int*) ; 
 float emscripten_get_now () ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  program ; 
 float sinf (float) ; 

void draw()
{
  int w, h;
  emscripten_get_canvas_element_size("#canvas", &w, &h);
  float t = emscripten_get_now() / 1000.0f;
  float xs = (float)h / w;
  float ys = 1.0f;
  float mat[] = { cosf(t) * xs, sinf(t) * ys, 0, 0, -sinf(t) * xs, cosf(t) * ys, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
  glUniformMatrix4fv(glGetUniformLocation(program, "mat"), 1, 0, mat);
  glClearColor(0,0,1,1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}