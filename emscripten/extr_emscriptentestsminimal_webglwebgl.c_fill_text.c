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
 int /*<<< orphan*/  fill_char (float,float,float,float,float,float,int /*<<< orphan*/ ,int,int) ; 

void fill_text(float x0, float y0, float r, float g, float b, float a, const char *str, float spacing, int charSize, int shadow)
{
  while(*str)
  {
    fill_char(x0, y0, r, g, b, a, *str++, charSize, shadow);
    x0 += spacing;
  }
}