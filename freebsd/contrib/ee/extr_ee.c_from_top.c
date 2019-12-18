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
struct text {struct text* next_line; } ;

/* Variables and functions */
 int absolute_lin ; 
 struct text* curr_line ; 
 struct text* first_line ; 

void 
from_top()
{
	struct text *tmpline = first_line;
	int x = 1;

	while ((tmpline != NULL) && (tmpline != curr_line))
	{
		x++;
		tmpline = tmpline->next_line;
	}
	absolute_lin = x;
}