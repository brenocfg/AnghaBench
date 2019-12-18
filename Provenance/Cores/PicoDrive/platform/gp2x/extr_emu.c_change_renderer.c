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
struct TYPE_2__ {int renderer32x; int renderer; } ;

/* Variables and functions */
 int PAHW_32X ; 
 int PAHW_SMS ; 
 int PicoAHW ; 
 int RT_8BIT_FAST ; 
 int RT_COUNT ; 
 TYPE_1__ currentConfig ; 

__attribute__((used)) static void change_renderer(int diff)
{
	int *r;
	if (PicoAHW & PAHW_32X)
		r = &currentConfig.renderer32x;
	else
		r = &currentConfig.renderer;
	*r += diff;

	// 8bpp fast is not there (yet?)
	if ((PicoAHW & PAHW_SMS) && *r == RT_8BIT_FAST)
		(*r)++;

	if      (*r >= RT_COUNT)
		*r = 0;
	else if (*r < 0)
		*r = RT_COUNT - 1;
}