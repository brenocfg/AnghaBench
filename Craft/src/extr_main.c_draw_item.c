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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  draw_triangles_3d_ao (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void draw_item(Attrib *attrib, GLuint buffer, int count) {
    draw_triangles_3d_ao(attrib, buffer, count);
}