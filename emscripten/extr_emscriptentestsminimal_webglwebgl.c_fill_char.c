#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_textured_rectangle (float,float,float,float,float,float,float,float,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_or_cache_character (unsigned int,int,int) ; 

void fill_char(float x0, float y0, float r, float g, float b, float a, unsigned int ch, int charSize, int shadow)
{
  fill_textured_rectangle(x0, y0, x0+charSize, y0+charSize, r, g, b, a, find_or_cache_character(ch, charSize, shadow)->texture);
}