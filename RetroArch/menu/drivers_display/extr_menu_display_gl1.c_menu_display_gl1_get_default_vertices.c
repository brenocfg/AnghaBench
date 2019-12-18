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
 float const* gl1_menu_vertexes ; 

__attribute__((used)) static const float *menu_display_gl1_get_default_vertices(void)
{
   return &gl1_menu_vertexes[0];
}