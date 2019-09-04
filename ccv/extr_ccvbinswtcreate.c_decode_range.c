#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int enable; void* max_value; void* step; void* min_value; } ;
typedef  TYPE_1__ ccv_swt_range_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char*) ; 
 void* strtod (char*,int /*<<< orphan*/ ) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void decode_range(const char* arg, ccv_swt_range_t* range)
{
	range->enable = 0;
	if (strcmp(arg, "x") && strcmp(arg, "X"))
	{
		char* pch = strtok((char*)arg, ",");
		if (pch)
		{
			range->min_value = strtod(pch, 0);
			pch = strtok(0, ",");
			if (pch)
			{
				range->step = strtod(pch, 0);
				pch = strtok(0, ",");
				if (pch)
				{
					range->max_value = strtod(pch, 0);
					range->enable = 1;
				}
			}
		}
	}
}